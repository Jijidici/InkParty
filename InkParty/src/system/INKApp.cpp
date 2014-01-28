/* ***********************************************************************
	INKApp.cpp - @Jijidici - 09/01/2014
************************************************************************ */

#include "system/INKApp.h"

#include "SDL.h"
#include "glm.hpp"
#include "renderer/INKRenderer.h"
#include "renderer/shapes/INKCustomShape.h"
#include "renderer/shaders/vs_particle.h"
#include "renderer/shaders/fs_particle.h"
#include "event/INKEventManager.h"
#include "event/INKQuitEvent.h"
#include "event/INKKeyEvent.h"
#include "physics/INKParticle.h"
#include "physics/forces/INKConstantForce.h"
#include "physics/forces/INKHookForce.h"
#include "physics/forces/INKBrakeForce.h"

INKApp::INKApp() 
	: _pMainFrame(0)
	, _bLoop(true) {

}

void INKApp::OnExecute() {
	init();
	launch();
	quit();
}

void INKApp::onEvent(INKEvent* pE) {
	if(pE->getType() == eQuitEvent) {
		_bLoop = false;
	}

	else if(pE->getType() == eKeyEvent) {
		INKKeyEvent* pKeyE = static_cast<INKKeyEvent*>(pE);
		if(pKeyE->getKey().unicode != 0 && pKeyE->getKey().unicode == 'q') {
			_bLoop = false;
		}
	}
}

void INKApp::init() {
	//frame
	_pMainFrame = new INKFrame("INK PARTY !", 400, 600, 32);
	_pMainFrame->init(60);

	//events
	INKEventManager::getInstance()->addListener(this, eQuitEvent);
	INKEventManager::getInstance()->addListener(this, eKeyEvent);

	//test zone
	_pCamera = new INKCamera(_pMainFrame->getRatio());
	INKRenderer::getInstance()->setCurrentCamera(_pCamera);

	std::vector<glm::vec3> quad1;
	quad1.push_back(glm::vec3(-10.f,	-12.f, 0.f));
	quad1.push_back(glm::vec3( 10.f,	-12.f, 0.f));
	quad1.push_back(glm::vec3( 10.f,	-13.f, 0.f));
	quad1.push_back(glm::vec3(-10.f,	-13.f, 0.f));

	std::vector<glm::vec3> quad2;
	quad2.push_back(glm::vec3(-10.f, -4.f, 0.f));
	quad2.push_back(glm::vec3(-2.f, -14.f, 0.f));
	quad2.push_back(glm::vec3(-3.5f, -14.f, 0.f));
	quad2.push_back(glm::vec3(-10.f, -5.5f, 0.f));

	std::vector<glm::vec3> quad3;
	quad3.push_back(glm::vec3(2.f, -14.f, 0.f));
	quad3.push_back(glm::vec3(3.5f, -4.f, 0.f));
	quad3.push_back(glm::vec3(4.5f, -4.f, 0.f));
	quad3.push_back(glm::vec3(3.f, -14.f, 0.f));

	std::vector<glm::vec3> quad4;
	quad4.push_back(glm::vec3(-10.f,	5.f, 0.f));
	quad4.push_back(glm::vec3( 1.f,		3.f, 0.f));
	quad4.push_back(glm::vec3( 1.f,		2.f, 0.f));
	quad4.push_back(glm::vec3(-10.f,	4.f, 0.f));

	std::vector<glm::vec3> quad5;
	quad5.push_back(glm::vec3( -1.f,	-3.f, 0.f));
	quad5.push_back(glm::vec3( 10.f,	2.f, 0.f));
	quad5.push_back(glm::vec3( 10.f,	1.f, 0.f));
	quad5.push_back(glm::vec3( -1.f,	-4.f, 0.f));

	std::vector<glm::vec3> quad6;
	quad6.push_back(glm::vec3(-10.f,	12.f, 0.f));
	quad6.push_back(glm::vec3( -9.f,	12.f, 0.f));
	quad6.push_back(glm::vec3( -9.f,	3.f, 0.f));
	quad6.push_back(glm::vec3( -10.f,	3.f, 0.f));

	std::vector<glm::vec3> quad7;
	quad7.push_back(glm::vec3(  9.f,	12.f, 0.f));
	quad7.push_back(glm::vec3( 10.f,	12.f, 0.f));
	quad7.push_back(glm::vec3(  10.f,	1.f, 0.f));
	quad7.push_back(glm::vec3(  9.f,	1.f, 0.f));

	_pPartSystem = new INKFluidParticleSystem(20, static_cast<int>(20.f*_pMainFrame->getRatio()), 1);
	_pPartSystem->setSpringRigidity(5.f, 1.f);
	_pPartSystem->setSpringLengths(0.6f, 0.3f);
	_pPartSystem->setBrakeCoef(0.0001f);
	_pPartSystem->setInfluenceDelta(0.1f);
	_pPartSystem->addParticles(512, 0.3f);
	_pPartSystem->addForce(new INKConstantForce(glm::vec3(0.f, -3.f, 0.f)));
	_pPartSystem->addSolid(new INKPhysicSolid(quad1, 1.f));
	_pPartSystem->addSolid(new INKPhysicSolid(quad2, 1.f));
	_pPartSystem->addSolid(new INKPhysicSolid(quad3, 1.f));
	_pPartSystem->addSolid(new INKPhysicSolid(quad4, 1.f));
	_pPartSystem->addSolid(new INKPhysicSolid(quad5, 1.f));
	_pPartSystem->addSolid(new INKPhysicSolid(quad6, 1.f));
	_pPartSystem->addSolid(new INKPhysicSolid(quad7, 1.f));
	INKRenderer::getInstance()->add(_pPartSystem);

	_pParticleProgram = new INKGLProgram();
	_pParticleProgram->buildProgram(inkshaders::vs_particle, inkshaders::fs_particle);
	for(int i=0; i<_pPartSystem->getParticlesCount(); ++i) {
		_pPartSystem->getParticle(i)->setProgram(_pParticleProgram);
	}
	//test zone
}

void INKApp::launch() {
	float fDt = 0.f;

	while(_bLoop) {
		_pMainFrame->saveFrameStartTime();

		INKRenderer::getInstance()->render();

		INKEventManager::getInstance()->manageEvent(_pMainFrame);

		_pPartSystem->update(fDt);

		fDt = _pMainFrame->computeFrameTime();
	}
}

void INKApp::quit() {
	//free the window system
	if(_pMainFrame != 0) {
		_pMainFrame->quit();
		delete _pMainFrame;
		_pMainFrame = 0;
	}

	delete _pPartSystem;
	delete _pCamera;
	delete _pParticleProgram;
}