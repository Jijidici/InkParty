/* ***********************************************************************
	INKDynamicSpringForce.cpp - @Jijidici - 26/01/2014
************************************************************************ */

#include "physics/forces/INKDynamicSpringForce.h"

#include <algorithm>

static INKDynamicSpringForce* _pInstance = nullptr;

INKDynamicSpringForce::INKDynamicSpringForce() {

}

INKDynamicSpringForce* INKDynamicSpringForce::getInstance() {
	if(_pInstance == nullptr) {
		_pInstance = new INKDynamicSpringForce();
	}

	return _pInstance;
}

void INKDynamicSpringForce::apply(INKParticleSystem* pSystem, int iP1Id, int iP2Id, float fK, float fL, float fV, float fDt) {
	float fEpsilon = 0.001f;
	glm::vec3 p1p2 = pSystem->getPosition(iP2Id) - pSystem->getPosition(iP1Id);
	float d = sqrt(glm::dot(p1p2, p1p2));

	glm::vec3 forceHook = (fK*(1-(fL/std::max(d, fEpsilon)))) * p1p2;
	glm::vec3 brakeForce = glm::vec3(0.f);
	if(fDt != 0) {
		brakeForce = fV/fDt * (pSystem->getVelocity(iP2Id) - pSystem->getVelocity(iP1Id));
	}

	pSystem->accumForce(iP1Id, forceHook+brakeForce);
	pSystem->accumForce(iP2Id, -(forceHook+brakeForce));
}