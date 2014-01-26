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

void INKParticleSystem::addRandomParticles(int iParticleCount, int amplitude) {
	std::srand(std::time(nullptr));

	for(int i=0; i<iParticleCount; ++i) {
		INKParticle* pNewParticle = new INKParticle();
		pNewParticle->setPosition(glm::vec3((std::rand()%(2*amplitude))-amplitude, (std::rand()%(2*amplitude))-amplitude, 0.f));
		pNewParticle->setMass((std::rand()%(2*amplitude))-amplitude);
		_particles.push_back(pNewParticle);
	}
}