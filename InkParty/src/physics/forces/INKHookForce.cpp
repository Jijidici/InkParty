/* ***********************************************************************
	INKHookForce.cpp - @Jijidici - 27/01/2014
************************************************************************ */

#include "physics/forces/INKHookForce.h"

#include <algorithm>
#include "glm.hpp"
#include "physics/INKParticleSystem.h"

INKHookForce::INKHookForce(float fK, float fL)
	: _fK(fK)
	, _fL(fL) {

}

INKHookForce::~INKHookForce() {

}

void INKHookForce::apply(INKParticleSystem* pSystem) {
	float fEpsilon = 0.001;

	for(std::vector<INKParticle*>::iterator itP1=pSystem->getParticles().begin(); itP1!=pSystem->getParticles().end(); ++itP1) {
		for(std::vector<INKParticle*>::iterator itP2=itP1+1; itP2!=pSystem->getParticles().end(); ++itP2) {
			glm::vec3 p1p2 = (*itP2)->getPosition() - (*itP1)->getPosition();
			float d = sqrt(glm::dot(p1p2, p1p2));
			glm::vec3 forceHook = (_fK*(1-(_fL/std::max(d, fEpsilon)))) * p1p2;

			(*itP1)->addForce(forceHook);
			(*itP2)->addForce(-forceHook);
		}
	}
}