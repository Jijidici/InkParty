/* ***********************************************************************
	INKRenderable.cpp - @Jijidici - 14/01/2014
************************************************************************ */

#include "renderer/INKRenderable.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "renderer/INKRenderer.h"
#include "renderer/shapes/INKCustomShape.h"

INKRenderable::INKRenderable(INKShape* pShape)
	: _position(glm::vec3(0.f))
	, _scale(glm::vec3(1.f))
	, _fRotation(0.f)
	, _pShape(pShape)
	, _pProgram(INKRenderer::getInstance()->getDefaultShaderProgram()){

}

INKRenderable::~INKRenderable() {
	INKCustomShape* pCustomShape = dynamic_cast<INKCustomShape*>(_pShape);
	if(pCustomShape != nullptr) {
		delete _pShape;
		_pShape = nullptr;
	}
}

void INKRenderable::render() {
	_pProgram->use();
	_pProgram->updateUniforms();

	glm::mat4 modelMatrix = glm::mat4(1.f);
	modelMatrix = glm::translate(modelMatrix, _position);
	modelMatrix = glm::scale(modelMatrix, _scale);
	modelMatrix = glm::rotate(modelMatrix, _fRotation, glm::vec3(0., 0., 1.));
	_pProgram->sendModelUniform(modelMatrix);

	_pShape->draw();
}