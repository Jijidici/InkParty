/* ***********************************************************************
	INKFluidParticleSystem.cpp - @Jijidici - 28/01/2014
************************************************************************ */

#include "physics/INKFluidParticleSystem.h"

#include "physics/forces/INKDynamicSpringForce.h"

INKFluidParticleSystem::INKFluidParticleSystem(int iMaxCount, float fStandardMass, int iSpaceWidth, int iSpaceHeight, float fCellSize) 
	: INKParticleSystem(iMaxCount, fStandardMass)
	, _iSpaceW(iSpaceWidth)
	, _iSpaceH(iSpaceHeight) 
	, _fCellSize(fCellSize)
	, _iCellInWidthCount(static_cast<int>(_iSpaceW/_fCellSize))
	, _iCellInHeightCount(static_cast<int>(_iSpaceH/_fCellSize)){

		_grid.resize(_iCellInWidthCount*_iCellInHeightCount);
}

INKFluidParticleSystem::~INKFluidParticleSystem() {

}

void INKFluidParticleSystem::update(float fDt) {
	updateGrid();

	for(int idPart=0; idPart<_iParticleCount; ++idPart) {
		int i = static_cast<int>((_positions[idPart].x+(_iSpaceW/2.f))/_fCellSize);
		int j = static_cast<int>((_positions[idPart].y+(_iSpaceH/2.f))/_fCellSize);

		if(i>=0 && i<_iCellInWidthCount && j>=0 && j<_iCellInHeightCount) {
			std::vector<int> neightbors = _grid[i + j*_iCellInWidthCount];
			if(i != 0) { 
				std::vector<int> l_neighbors = _grid[i-1 + j*_iCellInWidthCount];
				neightbors.insert(neightbors.end(), l_neighbors.begin(), l_neighbors.end());
			}

			if(i != _iCellInWidthCount-1) { 
				std::vector<int> r_neighbors = _grid[i+1 + j*_iCellInWidthCount];
				neightbors.insert(neightbors.end(), r_neighbors.begin(), r_neighbors.end());
			}

			if(j != 0) { 
				std::vector<int> t_neighbors = _grid[i-1 + (j-1)*_iCellInWidthCount];
				neightbors.insert(neightbors.end(), t_neighbors.begin(), t_neighbors.end());
			}

			if(j != _iCellInHeightCount-1) { 
				std::vector<int> b_neighbors = _grid[i-1 + (j+1)*_iCellInWidthCount];
				neightbors.insert(neightbors.end(), b_neighbors.begin(), b_neighbors.end());
			}

			for(std::vector<int>::iterator itId=neightbors.begin(); itId<neightbors.end(); ++itId) {
				if(idPart!=*itId) {

					float d = glm::length(_positions[*itId] - _positions[idPart]);
					//repulsion
					float fRepulsDist = (_mass[idPart] + _mass[*itId])*0.5f;
					if(d < fRepulsDist) {
						INKDynamicSpringForce::getInstance()->apply(this, idPart, *itId, _fRepulsiveSpringRigidity, _fRepulsiveSpringLength, _fBrakeCoef, fDt);
					}

					//attraction
					else if(d < fRepulsDist + 2.f*_fInfluenceDelta) {
						INKDynamicSpringForce::getInstance()->apply(this, idPart, *itId, _fAttractiveSpringRigidity, _fAttractiveSpringLength, _fBrakeCoef, fDt);
					}
				}
			}
		}
	}

	INKParticleSystem::update(fDt);
}

void INKFluidParticleSystem::updateGrid() {
	//clear
	for(std::vector<std::vector<int>>::iterator it=_grid.begin(); it!=_grid.end(); ++it) {
		it->clear();
	}

	for(int idPart=0; idPart<_iParticleCount; ++idPart) {
		int i = static_cast<int>((_positions[idPart].x+(_iSpaceW/2.f))/_fCellSize);
		int j = static_cast<int>((_positions[idPart].y+(_iSpaceH/2.f))/_fCellSize);
		if(i>=0 && i<_iCellInWidthCount && j>=0 && j<_iCellInHeightCount) {
			int idx = i + j*_iCellInWidthCount;

			_grid[idx].push_back(idPart);
		}
	}
}