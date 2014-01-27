/* ***********************************************************************
	INKBrakeForce.cpp - @Jijidici - 27/01/2014
************************************************************************ */

#include "physics/forces/INKBrakeForce.h"

#include "glm.hpp"
#include "physics/INKParticleSystem.h"
#include "physics/INKQuadTreeParticleSystem.h"

INKBrakeForce::INKBrakeForce(float fV)
	: _fV(fV) {

}

INKBrakeForce::~INKBrakeForce() {

}

void INKBrakeForce::apply(INKParticleSystem* pSystem) {
	if(_fDt != 0) {
		glm::vec3 brakeForce = glm::vec3(0.f);;

		INKQuadTreeParticleSystem* pGraphSystem = dynamic_cast<INKQuadTreeParticleSystem*>(pSystem);
		if(pGraphSystem == nullptr) { //apply force between each particle
			for(std::vector<INKParticle*>::iterator itP1=pSystem->getParticles().begin(); itP1!=pSystem->getParticles().end(); ++itP1) {
				for(std::vector<INKParticle*>::iterator itP2=itP1+1; itP2!=pSystem->getParticles().end(); ++itP2) {
					brakeForce = _fV/_fDt * ((*itP2)->getVelocity() - (*itP1)->getVelocity());

					(*itP1)->addForce(brakeForce);
					(*itP2)->addForce(-brakeForce);
				}
			}
		} else { //apply force between linked particles, considering the system graph
			TParticleGraph workingGraph = pGraphSystem->getGraph();

			for(unsigned int i=0; i<workingGraph.size(); ++i) {
				INKParticle* pP1 = pGraphSystem->getParticle(workingGraph[i].first);
				INKParticle* pP2 = pGraphSystem->getParticle(workingGraph[i].second);
				brakeForce = _fV/_fDt * (pP2->getVelocity() - pP1->getVelocity());

				pP1->addForce(brakeForce);
				pP2->addForce(-brakeForce);
			}
		}
	}
}