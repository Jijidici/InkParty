/* ***********************************************************************
	INKFluidParticleSystem.cpp - @Jijidici - 28/01/2014
************************************************************************ */

#include "physics/INKFluidParticleSystem.h"

#include "physics/forces/INKDynamicSpringForce.h"

INKFluidParticleSystem::INKFluidParticleSystem(int iSpaceWidth, int iSpaceHeight, float fCellSize) 
	: _iSpaceW(iSpaceWidth)
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

	for(unsigned int idPart=0; idPart<_particles.size(); ++idPart) {
		INKParticle* pP1 = _particles[idPart];
		glm::vec3 currentPos = pP1->getPosition();
		int i = (currentPos.x+(_iSpaceW/2.f))/static_cast<int>(_fCellSize);
		int j = (currentPos.y+(_iSpaceH/2.f))/static_cast<int>(_fCellSize);

		if(i>=0 && i<_iCellInWidthCount && j>=0 && j<_iCellInHeightCount) {
			int idx = i + j*_iCellInWidthCount;

			std::vector<int> neightbors = _grid[idx];
			for(std::vector<int>::iterator itId=neightbors.begin(); itId<neightbors.end(); ++itId) {
				if(idPart!=*itId) {
					INKParticle* pP2 = _particles[*itId];

					float d = glm::length(pP2->getPosition() - pP1->getPosition());
					//repulsion
					if(d < (pP1->getMass() + pP2->getMass())*0.5f) {
						INKDynamicSpringForce::getInstance()->apply(pP1, pP2, _fRepulsiveSpringRigidity, _fRepulsiveSpringLength, _fBrakeCoef, fDt);
					}

					//attraction
					else if(d < (pP1->getMass() + pP2->getMass())*0.5f + 2.f*_fInfluenceDelta) {
						INKDynamicSpringForce::getInstance()->apply(pP1, pP2, _fAttractiveSpringRigidity, _fAttractiveSpringLength, _fBrakeCoef, fDt);
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

	for(unsigned int idPart=0; idPart<_particles.size(); ++idPart) {
		glm::vec3 currentPos = _particles[idPart]->getPosition();
		int i = (currentPos.x+(_iSpaceW/2.f))/static_cast<int>(_fCellSize);
		int j = (currentPos.y+(_iSpaceH/2.f))/static_cast<int>(_fCellSize);
		if(i>=0 && i<_iCellInWidthCount && j>=0 && j<_iCellInHeightCount) {
			int idx = i + j*_iCellInWidthCount;

			_grid[idx].push_back(idPart);
		}
	}
}