/* ***********************************************************************
	INKFluidParticleSystem.cpp - @Jijidici - 28/01/2014
************************************************************************ */

#include "physics/INKFluidParticleSystem.h"

#include "physics/forces/INKDynamicSpringForce.h"

INKFluidParticleSystem::INKFluidParticleSystem() {

}

INKFluidParticleSystem::~INKFluidParticleSystem() {

}

void INKFluidParticleSystem::update(float fDt) {

	for(unsigned int i=0; i<_particles.size(); ++i) {
		INKParticle* pP1 = _particles[i];
		for(unsigned int j=0; j<_particles.size(); ++j) {
			if(i!=j) {
				INKParticle* pP2 = _particles[j];

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

	INKParticleSystem::update(fDt);
}