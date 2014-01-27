/* ***********************************************************************
	INKHookForce.cpp - @Jijidici - 27/01/2014
************************************************************************ */

#include "physics/forces/INKHookForce.h"

#include <algorithm>
#include "glm.hpp"
#include "physics/INKParticleSystem.h"
#include "physics/INKQuadTreeParticleSystem.h"

INKHookForce::INKHookForce(float fK, float fL)
	: _fK(fK)
	, _fL(fL) {

}

INKHookForce::~INKHookForce() {

}

void INKHookForce::apply(INKParticleSystem* pSystem) {
	float fEpsilon = 0.001f;
	glm::vec3 p1p2 = glm::vec3(0.f);
	float d = 0.f;
	glm::vec3 forceHook = glm::vec3(0.f);

	INKQuadTreeParticleSystem* pGraphSystem = dynamic_cast<INKQuadTreeParticleSystem*>(pSystem);
	if(pGraphSystem == nullptr) { //apply force between each particle
		for(std::vector<INKParticle*>::iterator itP1=pSystem->getParticles().begin(); itP1!=pSystem->getParticles().end(); ++itP1) {
			for(std::vector<INKParticle*>::iterator itP2=itP1+1; itP2!=pSystem->getParticles().end(); ++itP2) {
				p1p2 = (*itP2)->getPosition() - (*itP1)->getPosition();
				d = sqrt(glm::dot(p1p2, p1p2));
				forceHook = (_fK*(1-(_fL/std::max(d, fEpsilon)))) * p1p2;

				(*itP1)->addForce(forceHook);
				(*itP2)->addForce(-forceHook);
			}
		}
	} else { //apply force between linked particles, considering the system graph
		TParticleGraph workingGraph = pGraphSystem->getGraph();

		for(unsigned int i=0; i<workingGraph.size(); ++i) {
			INKParticle* pP1 = pGraphSystem->getParticle(workingGraph[i].first);
			INKParticle* pP2 = pGraphSystem->getParticle(workingGraph[i].second);

			p1p2 = pP2->getPosition() - pP1->getPosition();
			d = sqrt(glm::dot(p1p2, p1p2));
			forceHook = (_fK*(1.f-(_fL/std::max(d, fEpsilon)))) * p1p2;

			pP1->addForce(forceHook);
			pP2->addForce(-forceHook);
		}
	}
}