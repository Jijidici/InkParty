/* ***********************************************************************
	INKRenderer.cpp - @Jijidici - 14/01/2014
************************************************************************ */

#include "renderer\INKRenderer.h"

#include <stdexcept>
#include "GL/glew.h"
#include "SDL.h"

static INKRenderer* _pInstance = nullptr;

INKRenderer* INKRenderer::getInstance() {
	if(_pInstance == nullptr) {
		_pInstance = new INKRenderer();
	}

	return _pInstance;
}

void INKRenderer::init() {
	GLenum glewCode = glewInit();
	if(GLEW_OK != glewCode) {
		throw std::runtime_error("Unable to initialize GLEW");
	}
	
	glClearColor(0.1f, 0.2f, 0.3f, 1.f);
}

void INKRenderer::render() {
	glClear(GL_COLOR_BUFFER_BIT);

	SDL_GL_SwapBuffers();
}

INKRenderer::INKRenderer() {

}

INKRenderer::~INKRenderer() {
	_pInstance = nullptr;
}