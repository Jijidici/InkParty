/* ***********************************************************************
	INKConstantForce.h - @Jijidici - 27/01/2014
************************************************************************ */

#include "physics/forces/INKConstantForce.h"

#include "physics/INKParticleSystem.h"

INKConstantForce::INKConstantForce(glm::vec3 initialForce)
	: _force(initialForce) {

}

INKConstantForce::~INKConstantForce() {

}

void INKConstantForce::apply(INKParticleSystem* pSystem) {
	for(std::vector<INKParticle*>::iterator itPart=pSystem->getParticles().begin(); itPart!=pSystem->getParticles().end(); ++itPart) {
		(*itPart)->addForce(_force);
	}
}