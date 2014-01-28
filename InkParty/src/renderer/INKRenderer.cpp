/* ***********************************************************************
	INKRenderer.cpp - @Jijidici - 14/01/2014
************************************************************************ */

#include "renderer\INKRenderer.h"

#include <stdexcept>
#include "GL/glew.h"
#include "SDL.h"

#include "renderer/shaders/vs_default.h"
#include "renderer/shaders/fs_default.h"
#include "physics/INKParticle.h"
#include "physics/INKPhysicSolid.h"

static INKRenderer* _pInstance = nullptr;

INKRenderer::INKRenderer() 
	: _pSquareModel(nullptr) {

}

INKRenderer::~INKRenderer() {
	if(_pSquareModel != nullptr) {
		delete _pSquareModel;

		_toRender.clear();

		_pSquareModel = nullptr;
	}

	_pInstance = nullptr;
}

INKRenderer* INKRenderer::getInstance() {
	if(_pInstance == nullptr) {
		_pInstance = new INKRenderer();
		_pInstance->init();
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

	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for(std::vector<INKRenderable*>::iterator itRend=_toRender.begin(); itRend!=_toRender.end(); ++itRend) {
		(*itRend)->render();
	}

	glDisable(GL_BLEND);

	SDL_GL_SwapBuffers();
}

void INKRenderer::add(INKRenderable* aRenderable) {
	_toRender.push_back(aRenderable);
}

void INKRenderer::add(INKParticleSystem* pSystem) {
	for(std::vector<INKPhysicSolid*>::iterator it=pSystem->getSolids().begin(); it!=pSystem->getSolids().end(); ++it) {
		add(*it);
	}
	
	for(std::vector<INKParticle*>::iterator it=pSystem->getParticles().begin(); it!=pSystem->getParticles().end(); ++it) {
		add(*it);
	}
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
		_pDefaultShaderProgram->buildProgram(inkshaders::vs_default, inkshaders::fs_default);
	}
	
	return _pDefaultShaderProgram;
}
