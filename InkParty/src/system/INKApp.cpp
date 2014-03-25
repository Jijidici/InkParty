/* ***********************************************************************
	INKApp.cpp - @Jijidici - 09/01/2014
************************************************************************ */

#define _USE_MATH_DEFINES

#include "system/INKApp.h"

#include <cmath>
#include <iostream>
#include "SDL.h"
#include "glm.hpp"
#include "renderer/INKRenderer.h"
#include "renderer/INKRenderable.h"
#include "renderer/shapes/INKCustomShape.h"
#include "event/INKEventManager.h"
#include "event/INKQuitEvent.h"
#include "event/INKKeyEvent.h"
#include "event/INKMouseDownEvent.h"
#include "physics/INKParticle.h"
#include "physics/INKHexagon.h"
#include "physics/INKPhysicSolid.h"
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
		else if(pKeyE->getKey().sym == SDLK_SPACE) {
			_pPartSystem->reset();
		}
		else if(pKeyE->getKey().sym == 'e') {
			float fSpringStrength = _pPartSystem->getSpringStrength();
			fSpringStrength+=2.f;
			_pPartSystem->setSpringStrength(fSpringStrength);
			std::cout << ">> Spring rigidity : " << fSpringStrength << std::endl;
		}
		else if(pKeyE->getKey().sym == 'd') {
			float fSpringStrength = _pPartSystem->getSpringStrength();
			fSpringStrength-=2.f;
			if(fSpringStrength < 0.f) { fSpringStrength = 0.f; }
			_pPartSystem->setSpringStrength(fSpringStrength);
			std::cout << ">> Spring rigidity : " << fSpringStrength << std::endl;
		}
	}

	else if(pE->getType() == eMouseDownEvent) {
		INKMouseDownEvent* pMouseDownE = static_cast<INKMouseDownEvent*>(pE);
		glm::vec3 clickPos;
		clickPos.x = (pMouseDownE->getMousePos().x/_pMainFrame->getWidth())*2.f -1.f;
		clickPos.y = -((pMouseDownE->getMousePos().y/_pMainFrame->getHeight())*2.f -1.f);
		clickPos.z = 0.f;

		_pPartSystem->addOneParticle(10.f*clickPos);
	}
}

void INKApp::init() {
	//frame
	_pMainFrame = new INKFrame("INK PARTY !", 600, 600, 32);
	_pMainFrame->init(60);

	//events
	INKEventManager::getInstance()->addListener(this, eQuitEvent);
	INKEventManager::getInstance()->addListener(this, eKeyEvent);
	INKEventManager::getInstance()->addListener(this, eMouseDownEvent);

	//test zone
	_pCamera = new INKCamera(_pMainFrame->getRatio());
	INKRenderer::getInstance()->setCurrentCamera(_pCamera);

	_pPartSystem = new INKGooParticleSystem(256, 0.3f, 2.f, 0.2f);
	INKRenderer::getInstance()->add(_pPartSystem);
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