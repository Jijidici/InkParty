/* ***********************************************************************
	INKBrakeForce.cpp - @Jijidici - 27/01/2014
************************************************************************ */

#include "physics/forces/INKBrakeForce.h"

#include "glm.hpp"
#include "physics/INKParticleSystem.h"

INKBrakeForce::INKBrakeForce(float fV)
	: _fV(fV) {

}

INKBrakeForce::~INKBrakeForce() {

}

void INKBrakeForce::apply(INKParticleSystem* pSystem) {
	if(_fDt != 0) {
		for(std::vector<INKParticle*>::iterator itP1=pSystem->getParticles().begin(); itP1!=pSystem->getParticles().end(); ++itP1) {
			for(std::vector<INKParticle*>::iterator itP2=itP1+1; itP2!=pSystem->getParticles().end(); ++itP2) {
				glm::vec3 brakeForce = _fV/_fDt * ((*itP2)->getVelocity() - (*itP1)->getVelocity());

				(*itP1)->addForce(brakeForce);
				(*itP2)->addForce(-brakeForce);
			}
		}
	}
}