/* ***********************************************************************
	INKAttractiveForce.cpp - @Jijidici - 08/02/2014
************************************************************************ */

#include "physics/forces/INKAttractiveForce.h"

INKAttractiveForce::INKAttractiveForce(glm::vec3 attractionPoint, float fPower, float fBrakeCoef)
	: _attractionPoint(attractionPoint) 
	, _fPower(fPower)
	, _fBrakeCoef(fBrakeCoef) {

}

INKAttractiveForce::~INKAttractiveForce() {

}

void INKAttractiveForce::apply(INKParticleSystem* pSystem) {
	for(int i=0; i<pSystem->getParticleCount(); ++i) {
		glm::vec3 toAttracDir = glm::normalize(_attractionPoint - pSystem->getPosition(i));
		glm::vec3 currentSpeed = pSystem->getVelocity(i);

		float fPowerToApply = _fPower;
		if(glm::dot(currentSpeed, toAttracDir) <= 0.f) {
			fPowerToApply *= _fBrakeCoef;
		}
		pSystem->accumForce(i, fPowerToApply*toAttracDir);
	}
}