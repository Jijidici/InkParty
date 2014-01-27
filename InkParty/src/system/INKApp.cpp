/* ***********************************************************************
	INKApp.cpp - @Jijidici - 09/01/2014
************************************************************************ */

#include "system/INKApp.h"

#include "SDL.h"
#include "glm.hpp"
#include "renderer/INKRenderer.h"
#include "renderer/shapes/INKCustomShape.h"
#include "event/INKEventManager.h"
#include "event/INKQuitEvent.h"
#include "event/INKKeyEvent.h"
#include "physics/INKParticle.h"
#include "physics/forces/INKConstantForce.h"

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

	_pPartSystem = new INKParticleSystem();
	_pPartSystem->addRandomParticles(256, 10.);
	_pPartSystem->addForce(new INKConstantForce(glm::vec3(0., -1., 0.)));
	INKRenderer::getInstance()->add(_pPartSystem);

	std::vector<glm::vec3> testPoint;
	testPoint.push_back(glm::vec3(-10.f,	-10.f, 0.f));
	testPoint.push_back(glm::vec3(-9.f,		-10.f, 0.f));
	testPoint.push_back(glm::vec3(-10.f,	-12.f, 0.f));
	testPoint.push_back(glm::vec3(-9.f,		-11.f, 0.f));
	testPoint.push_back(glm::vec3( 10.f,	-12.f, 0.f));
	testPoint.push_back(glm::vec3( 9.f,		-11.f, 0.f));
	testPoint.push_back(glm::vec3( 10.f,	-10.f, 0.f));
	testPoint.push_back(glm::vec3( 9.f,		-10.f, 0.f));
	
	_pRendTest = new INKPhysicSolid(testPoint);
	INKRenderer::getInstance()->add(_pRendTest);
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

	delete _pRendTest;
	delete _pPartSystem;
	delete _pCamera;
}