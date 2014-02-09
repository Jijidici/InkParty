/* ***********************************************************************
	INKRenderer.cpp - @Jijidici - 14/01/2014
************************************************************************ */

#include "renderer\INKRenderer.h"

#include <stdexcept>
#include <cassert>
#include "SDL.h"
#include "gtc/matrix_transform.hpp"

#include "renderer/shaders/vs_default.h"
#include "renderer/shaders/fs_default.h"
#include "renderer/shaders/vs_particle.h"
#include "renderer/shaders/fs_particle.h"
#include "renderer/shaders/vs_well.h"
#include "renderer/shaders/fs_well.h"
#include "physics/INKParticle.h"
#include "physics/INKPhysicSolid.h"

static INKRenderer* _pInstance = nullptr;

INKRenderer::INKRenderer() 
	: _pSquareModel(nullptr) 
	, _pCurrentCamera(nullptr) {

}

INKRenderer::~INKRenderer() {
	if(_pSquareModel != nullptr) {
		delete _pSquareModel;
		_pSquareModel = nullptr;
	}

	for(std::vector<INKRenderable*>::iterator itRend=_renderRenderables.begin(); itRend!=_renderRenderables.end(); ++itRend) {
		delete *itRend;
	}

	//delete shaders
	for(std::map<std::string, INKGLProgram*>::iterator it=_shadersMap.begin(); it!=_shadersMap.end(); ++it) {
		delete it->second;
	}

	_renderSystems.clear();
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
	
	glClearColor(0.2f, 0.2f, 0.2f, 1.f);

	//build shaders
	addShader("default", inkshaders::vs_default, inkshaders::fs_default);
	addShader("particles", inkshaders::vs_particle, inkshaders::fs_particle);
	addShader("well", inkshaders::vs_well, inkshaders::fs_well);
}

void INKRenderer::render() {
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for(std::vector<INKParticleSystem*>::iterator itRend=_renderSystems.begin(); itRend!=_renderSystems.end(); ++itRend) {

		INKGLProgram* pDefaultProgram = getShader("default");
		pDefaultProgram->use();
		pDefaultProgram->updateUniforms();
		for(std::vector<INKPhysicSolid*>::iterator itSolid=(*itRend)->getSolids().begin(); itSolid!=(*itRend)->getSolids().end(); ++itSolid) {
			(*itSolid)->getShape()->draw();
		}

		for(std::vector<INKHexagon*>::iterator itHex=(*itRend)->getHexagons().begin(); itHex!=(*itRend)->getHexagons().end(); ++itHex) {
			(*itHex)->draw();
		}

		INKGLProgram* pParticleShader = getShader("particles");
		pParticleShader->use();
		pParticleShader->updateUniforms();
		for(int i=0; i<(*itRend)->getParticleCount(); ++i) {
			glm::mat4 modelMatrix = glm::mat4(1.f);
			modelMatrix = glm::translate(modelMatrix, (*itRend)->getPosition(i));
			modelMatrix = glm::scale(modelMatrix, glm::vec3((*itRend)->getMass(i)));
			pParticleShader->sendModelUniform(modelMatrix);

			getSquare()->draw();
		}
	}

	for(std::vector<INKRenderable*>::iterator itRend=_renderRenderables.begin(); itRend!=_renderRenderables.end(); ++itRend) {
		(*itRend)->render();
	}

	glDisable(GL_BLEND);

	SDL_GL_SwapBuffers();
}

void INKRenderer::addShader(std::string sTag, const GLchar* vsSource, const GLchar* fsSource) {
	INKGLProgram* pAddedProgram = new INKGLProgram();
	pAddedProgram->buildProgram(vsSource, fsSource);
	_shadersMap.insert(std::pair<std::string, INKGLProgram*>(sTag, pAddedProgram));
}

INKGLProgram* INKRenderer::getShader(std::string sTag) {
	std::map<std::string, INKGLProgram*>::iterator itRet = _shadersMap.find(sTag);
	assert(itRet != _shadersMap.end());
	return itRet->second;
}

INKSquareShape* INKRenderer::getSquare() {
	if(_pSquareModel == nullptr) {
		_pSquareModel = new INKSquareShape();
	}

	return _pSquareModel;
}
