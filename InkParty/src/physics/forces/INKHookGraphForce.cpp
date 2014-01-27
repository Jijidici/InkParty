/* ***********************************************************************
	INKHookGraphForce.cpp - @Jijidici - 27/01/2014
************************************************************************ */

#include "physics/forces/INKHookGraphForce.h"

#include <algorithm>
#include "glm.hpp"

INKHookGraphForce::INKHookGraphForce(float fK, float fL)
	: INKHookForce(fK, fL) {

}

INKHookGraphForce::~INKHookGraphForce() {

}

void INKHookGraphForce::apply(INKQuadTreeParticleSystem* pSystem) {
	float fEpsilon = 0.001f;
	TParticleGraph workingGraph = pSystem->getGraph();

	for(unsigned int i=0; i<workingGraph.size(); ++i) {
		INKParticle* pP1 = pSystem->getParticle(workingGraph[i].first);
		INKParticle* pP2 = pSystem->getParticle(workingGraph[i].second);

		glm::vec3 p1p2 = pP2->getPosition() - pP1->getPosition();
		float d = sqrt(glm::dot(p1p2, p1p2));
		glm::vec3 forceHook = (_fK*(1-(_fL/std::max(d, fEpsilon)))) * p1p2;

		pP1->addForce(forceHook);
		pP2->addForce(-forceHook);
	}
}