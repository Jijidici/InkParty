/* ***********************************************************************
	INKRenderable.cpp - @Jijidici - 14/01/2014
************************************************************************ */

#include "renderer/INKRenderable.h"

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

	_pShape->draw();
}