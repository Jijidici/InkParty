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

void INKRenderer::render(std::vector<INKRenderable*>& toRender) {
	glClear(GL_COLOR_BUFFER_BIT);

	for(std::vector<INKRenderable*>::iterator itRend=toRender.begin(); itRend!=toRender.end(); ++itRend) {
		(*itRend)->render();
	}

	SDL_GL_SwapBuffers();
}

INKSquareShape* INKRenderer::getSquare() {
	if(_pSquareModel == nullptr) {
		_pSquareModel = new INKSquareShape();
	}

	return _pSquareModel;
}

INKGLProgram* INKRenderer::getDefaultShaderProgram() {
	if(_pDefaultShaderProgram == nullptr) {
		_pDefaultShaderProgram = new INKGLProgram();
		_pDefaultShaderProgram->buildProgram(INKGLProgram::defaultVS, INKGLProgram::defaultFS);
	}
	
	return _pDefaultShaderProgram;
}

INKRenderer::INKRenderer() 
	: _pSquareModel(nullptr) {

}

INKRenderer::~INKRenderer() {
	if(_pSquareModel != nullptr) {
		delete _pSquareModel;
		_pSquareModel = nullptr;
	}

	_pInstance = nullptr;
}