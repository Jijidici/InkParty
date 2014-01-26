/* ***********************************************************************
	INKRenderable.cpp - @Jijidici - 14/01/2014
************************************************************************ */

#include "renderer/INKRenderable.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "renderer/INKRenderer.h"
#include "renderer/shapes/INKSquareShape.h"

INKRenderable::INKRenderable(INKSquareShape* pShape)
	: _pShape(pShape)
	, _pProgram(INKRenderer::getInstance()->getDefaultShaderProgram()){

}

INKRenderable::~INKRenderable() {

}

void INKRenderable::render() {
	_pProgram->use();
	_pProgram->updateUniforms();
	_pProgram->sendModelUniform(glm::translate(glm::mat4(1.f), glm::vec3(2.f, 2.f, 0.f)));

	_pShape->draw();
}