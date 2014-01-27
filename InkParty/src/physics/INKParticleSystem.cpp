/* ***********************************************************************
	INKParticleSystem.cpp - @Jijidici - 26/01/2014
************************************************************************ */

#include "physics/INKParticleSystem.h"

#include <cstdlib>
#include <ctime>
#include "glm.hpp"

INKParticleSystem::INKParticleSystem() {

}

INKParticleSystem::~INKParticleSystem() {
	for(std::vector<INKParticle*>::iterator itParticle=_particles.begin(); itParticle!=_particles.end(); ++itParticle) {
		delete *itParticle;
		*itParticle = nullptr;
	}
	_particles.clear();

	for(std::vector<INKForce*>::iterator itForce=_forcesToApply.begin(); itForce!=_forcesToApply.end(); ++itForce) {
		delete *itForce;
		*itForce = nullptr;
	}
	_forcesToApply.clear();
}

void INKParticleSystem::addRandomParticles(int iParticleCount, float fAmplitude) {
	std::srand(0);

	for(int i=0; i<iParticleCount; ++i) {
		INKParticle* pNewParticle = new INKParticle();
		float fRandX = 2.f*fAmplitude*(static_cast<float>(std::rand()%1000)/1000.f) - fAmplitude;
		float fRandY = 2.f*fAmplitude*(static_cast<float>(std::rand()%1000)/1000.f) - fAmplitude;
		float fMass = 1.f*(static_cast<float>(std::rand()%1000)/1000.f) + 0.2f;

		pNewParticle->setPosition(glm::vec3(fRandX, fRandY, 0.f));
		pNewParticle->setMass(fMass);
		_particles.push_back(pNewParticle);
	}
}

void INKParticleSystem::update(float fDt) {
	for(std::vector<INKForce*>::iterator itForce=_forcesToApply.begin(); itForce!=_forcesToApply.end(); ++itForce) {
		(*itForce)->apply(this);
	}

	leapFrogSolve(fDt);
}

void INKParticleSystem::leapFrogSolve(float fDt) {
	for(std::vector<INKParticle*>::iterator itPart=_particles.begin(); itPart!=_particles.end(); ++itPart) {
		INKParticle* pCurrentPart = *itPart;

		glm::vec3 nextVelocity = pCurrentPart->getVelocity() + fDt*(pCurrentPart->getForce()/pCurrentPart->getMass());
		pCurrentPart->setVelocity(nextVelocity);

		glm::vec3 nextPosition = pCurrentPart->getPosition() + fDt*nextVelocity;
		pCurrentPart->setPosition(nextPosition);

		pCurrentPart->setForce(glm::vec3(0.f));
	}
}