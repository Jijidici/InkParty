/* ***********************************************************************
	INKApp.cpp - @Jijidici - 09/01/2014
************************************************************************ */

#define _USE_MATH_DEFINES

#include "system/INKApp.h"

#include <cmath>
#include "SDL.h"
#include "glm.hpp"
#include "renderer/INKRenderer.h"
#include "renderer/INKRenderable.h"
#include "renderer/shapes/INKCustomShape.h"
#include "event/INKEventManager.h"
#include "event/INKQuitEvent.h"
#include "event/INKKeyEvent.h"
#include "event/INKMouseMoveEvent.h"
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
	}
}

void INKApp::init() {
	//frame
	_pMainFrame = new INKFrame("INK PARTY !", 600, 600, 32);
	_pMainFrame->init(60);

	//events
	INKEventManager::getInstance()->addListener(this, eQuitEvent);
	INKEventManager::getInstance()->addListener(this, eKeyEvent);

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