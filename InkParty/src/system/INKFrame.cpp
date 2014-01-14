/* ***********************************************************************
	INKFrame.cpp - @Jijidici - 09/01/2014
************************************************************************ */

#include "system/INKFrame.h"

#include <sstream>
#include <string>
#include <stdexcept>
#include "SDL.h"

INKFrame::INKFrame(std::string strTitle, int iW, int iH, int iBbp)
	: _strTitle(strTitle)
	, _iW(iW)
	, _iH(iH)
	, _iBbp(iBbp) {

}

void INKFrame::init(int iFps) {
	setFPS(iFps);

	//intialize SDL
	if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        throw std::runtime_error("Unable to initialize SDL");
    }

	SDL_WM_SetCaption(_strTitle.c_str(), 0);

	//open the window
	if(!SDL_SetVideoMode(_iW, _iH, _iBbp, SDL_OPENGL | SDL_GL_DOUBLEBUFFER )) {
        throw std::runtime_error("Unable to open a window");
    }

	SDL_EnableUNICODE(SDL_ENABLE);
}

void INKFrame::quit() {
	SDL_Quit();
}

bool INKFrame::pollEvent(SDL_Event& e) const {
	return SDL_PollEvent(&e);
}

float INKFrame::computeFrameTime() {
    int iCurrentTime = SDL_GetTicks();
	int iDiff = iCurrentTime - _iFrameStartTime;
	if(iDiff < _iFrameDuration) {
        SDL_Delay(_iFrameDuration - iDiff);
    }

	float fFrameDurationSc = 0.001f * (SDL_GetTicks() - _iFrameStartTime);
	std::stringstream titleWithFps;
	titleWithFps<<_strTitle<<" - "<<1.f/fFrameDurationSc<<"FPS";
	SDL_WM_SetCaption(titleWithFps.str().c_str(), 0);

	return fFrameDurationSc;
}