/* ***********************************************************************
	INKParticleSystem.cpp - @Jijidici - 26/01/2014
************************************************************************ */

#include "physics/INKParticleSystem.h"

#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "glm.hpp"

INKParticleSystem::INKParticleSystem(int iMaxCount, float fStandardMass) 
	: _iParticleCount(0) 
	, _iMaxPartCount(iMaxCount)
	, _fStandardMass(fStandardMass) {

	srand(static_cast<unsigned int>(time(NULL)));
}

INKParticleSystem::~INKParticleSystem() {
	_positions.clear();
	_velocities.clear();
	_forces.clear();
	_mass.clear();

	for(std::vector<INKForce*>::iterator itForce=_forcesToApply.begin(); itForce!=_forcesToApply.end(); ++itForce) {
		delete *itForce;
		*itForce = nullptr;
	}
	_forcesToApply.clear();

	for(std::vector<INKPhysicSolid*>::iterator itSolid=_solids.begin(); itSolid!=_solids.end(); ++itSolid) {
		delete *itSolid;
		*itSolid = nullptr;
	}
	_solids.clear();
}

void INKParticleSystem::addParticles(int iParticleCount, float fMass) {
	int iWidth = static_cast<int>(sqrt(iParticleCount));
	int iHeight = iParticleCount/iWidth;
	float fStep = fMass;

	for(int i=0; i<iParticleCount; ++i) {
		_positions.push_back(glm::vec3(fStep*(i%iWidth - iWidth/2) -0.f, fStep*(i/iWidth - iHeight/2) + 10.f, 0.f));
		_velocities.push_back(glm::vec3(0.f));
		_forces.push_back(glm::vec3(0.f));
		_mass.push_back(fMass);
		++_iParticleCount;
	}
}

void INKParticleSystem::update(float fDt) {
	//spawn
	if(_iParticleCount < _iMaxPartCount) {
		for(std::vector<glm::vec3>::iterator itSpawn=_spawners.begin(); itSpawn!=_spawners.end(); ++itSpawn) {
			_positions.push_back(*itSpawn + glm::vec3(0.1f*(rand()%10), 0.1f*(rand()%10), 0.f));
			_velocities.push_back(glm::vec3(0.f));
			_forces.push_back(glm::vec3(0.f));
			_mass.push_back(_fStandardMass);
			++_iParticleCount;
		}
	}

	for(std::vector<INKForce*>::iterator itForce=_forcesToApply.begin(); itForce!=_forcesToApply.end(); ++itForce) {
		(*itForce)->setDt(fDt);
		(*itForce)->apply(this);
	}

	if(fDt != 0.f) {
		for(int i=0; i<_iParticleCount; ++i) {
			glm::vec3 partNextPos;
			glm::vec3 partNextVel;
			getNextState(i, partNextPos, partNextVel, fDt);

			for(std::vector<INKPhysicSolid*>::iterator itSolid=_solids.begin(); itSolid!=_solids.end(); ++itSolid) {
				(*itSolid)->computeCollision(_positions[i], _mass[i], partNextPos, partNextVel, fDt, _forces[i]);
			}
		}
	}

	leapFrogSolve(fDt);
}

void INKParticleSystem::leapFrogSolve(float fDt) {
	for(int i=0; i<_iParticleCount; ++i) {
		glm::vec3 nextVelocity = _velocities[i] + fDt*(_forces[i]/_mass[i]);
		_velocities[i] = nextVelocity;

		glm::vec3 nextPosition = _positions[i] + fDt*nextVelocity;
		_positions[i] = nextPosition;

		_forces[i] = glm::vec3(0.f);
	}
}

void INKParticleSystem::getNextState(int iPartId, glm::vec3& nextPos, glm::vec3& nextVel, float fDt) {
	nextVel = _velocities[iPartId] + fDt*(_forces[iPartId]/_mass[iPartId]);
	nextPos = _positions[iPartId] + fDt*nextVel;
}