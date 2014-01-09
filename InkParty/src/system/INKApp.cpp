#include "system/INKApp.h"

#include <iostream>
#include "SDL.h"

INKApp::INKApp() 
	: _pMainFrame(0){

}

void INKApp::OnExecute() {
	init();
	launch();
	quit();
}

void INKApp::init() {
	_pMainFrame = new INKFrame("INK PARTY !", 400, 600, 32);
	_pMainFrame->init(60);
}

void INKApp::launch() {
	float fDt = 0.f;

	bool loop = true;
	while(loop) {
		_pMainFrame->saveFrameStartTime();

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