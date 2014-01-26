/* ***********************************************************************
	INKParticle.h - @Jijidici - 26/01/2014
************************************************************************ */

#include "physics/INKParticle.h"

#include "renderer/INKRenderer.h"

INKParticle::INKParticle()
	: INKRenderable(INKRenderer::getInstance()->getSquare()) 
	, _velocity(0.f)
	, _force(0.f)
	, _fMass(1.f) {

}

INKParticle::~INKParticle() {

}

void INKParticle::setMass(float fMass) {
	_fMass = fMass;
	_scale = glm::vec3(fMass);
}