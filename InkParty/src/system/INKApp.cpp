/* ***********************************************************************
	INKApp.cpp - @Jijidici - 09/01/2014
************************************************************************ */

#include "system/INKApp.h"

#include <iostream>
#include "SDL.h"

#include "event/INKEventManager.h"
#include "event/INKQuitEvent.h"
#include "event/INKKeyEvent.h"

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
	_pMainFrame = new INKFrame("INK PARTY !", 400, 600, 32);
	_pMainFrame->init(60);

	INKEventManager::getInstance()->addListener(this, eQuitEvent);
	INKEventManager::getInstance()->addListener(this, eKeyEvent);
}

void INKApp::launch() {
	float fDt = 0.f;

	while(_bLoop) {
		_pMainFrame->saveFrameStartTime();

		INKEventManager::getInstance()->manageEvent(_pMainFrame);

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
}