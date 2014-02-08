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
	for(int i=0; i<pSystem->getParticleCount(); ++i) {
		pSystem->accumForce(i, _force);
	}
}