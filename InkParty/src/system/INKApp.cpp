/* ***********************************************************************
	INKApp.cpp - @Jijidici - 09/01/2014
************************************************************************ */

#include "system/INKApp.h"

#include "SDL.h"
#include "renderer/INKRenderer.h"
#include "renderer/INKRenderable.h"
#include "renderer/shapes/INKSquareShape.h"
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
	//frame
	_pMainFrame = new INKFrame("INK PARTY !", 400, 600, 32);
	_pMainFrame->init(60);

	//renderer
	INKRenderer::getInstance()->init();

	//events
	INKEventManager::getInstance()->addListener(this, eQuitEvent);
	INKEventManager::getInstance()->addListener(this, eKeyEvent);
}

void INKApp::launch() {
	float fDt = 0.f;

	//test zone - begin
	INKSquareShape* square = new INKSquareShape();
	INKRenderable rendTest(square);
	//test zone - end

	while(_bLoop) {
		_pMainFrame->saveFrameStartTime();

		
		glClear(GL_COLOR_BUFFER_BIT);
		rendTest.render();
		SDL_GL_SwapBuffers();

		//INKRenderer::getInstance()->render();

		INKEventManager::getInstance()->manageEvent(_pMainFrame);

		fDt = _pMainFrame->computeFrameTime();
	}

	delete square;
}

void INKApp::quit() {
	//free the window system
	if(_pMainFrame != 0) {
		_pMainFrame->quit();
		delete _pMainFrame;
		_pMainFrame = 0;
	}
}