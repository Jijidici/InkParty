/* ***********************************************************************
	INKBrakeGraphForce.cpp - @Jijidici - 27/01/2014
************************************************************************ */

#include "physics/forces/INKBrakeGraphForce.h"

#include "glm.hpp"

INKBrakeGraphForce::INKBrakeGraphForce(float fV)
	: INKBrakeForce(fV) {

}

INKBrakeGraphForce::~INKBrakeGraphForce() {

}

void INKBrakeGraphForce::apply(INKQuadTreeParticleSystem* pSystem) {
	if(_fDt != 0) {
		TParticleGraph workingGraph = pSystem->getGraph();

		for(unsigned int i=0; i<workingGraph.size(); ++i) {
			INKParticle* pP1 = pSystem->getParticle(workingGraph[i].first);
			INKParticle* pP2 = pSystem->getParticle(workingGraph[i].second);
			glm::vec3 brakeForce = _fV/_fDt * (pP2->getVelocity() - pP1->getVelocity());

			pP1->addForce(brakeForce);
			pP2->addForce(-brakeForce);
		}
	}
}