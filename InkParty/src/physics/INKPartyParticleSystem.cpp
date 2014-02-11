/* ***********************************************************************
	INKPartyParticleSystem.cpp - @Jijidici - 11/02/2014
************************************************************************ */

#define _USE_MATH_DEFINES

#include <cstdlib>
#include <cmath>
#include <ctime>
#include "physics/INKPartyParticleSystem.h"
#include "physics/forces/INKAttractiveForce.h"
#include "renderer/INKRenderer.h"

INKPartyParticleSystem::INKPartyParticleSystem() 
	: INKFluidParticleSystem(256, 0.3f, 20, 20, 0.5f) {
	init();
}

void INKPartyParticleSystem::init() {
	setSpringRigidity(5.f, 2.f);
	setSpringLengths(0.3f, 0.3f);
	setBrakeCoef(0.00001f);
	setInfluenceDelta(0.2f);

	addForce(new INKAttractiveForce(glm::vec3(0.f), 1.5f, 2.f));
	addWell(glm::vec3(0.f, 0.f, 0.f));
	INKRenderable* pMainWell = new INKRenderable(INKRenderer::getInstance()->getSquare());
	pMainWell->setScale(glm::vec3(2.5f));
	pMainWell->setProgram(INKRenderer::getInstance()->getShader("well"));
	INKRenderer::getInstance()->add(pMainWell);

	srand(time(nullptr));
	float fStepAngle = (2.f*M_PI)/8.f;
	for(int i=0; i<3; ++i) {
		float fCurrentAlpha = (rand()%9)*fStepAngle;
		addSpawner(10.f*glm::vec3(cos(fCurrentAlpha), sin(fCurrentAlpha), 0.f));
	}

	addHexagon(new INKHexagon(8, 2.f));
	addHexagon(new INKHexagon(8, 5.f));

	_hexagons[0]->hideSegments(2);
	_hexagons[1]->hideSegments(3);
}

void INKPartyParticleSystem::update(float fDt) {

	INKFluidParticleSystem::update(fDt);
}