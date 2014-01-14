/* ***********************************************************************
	INKRenderable.cpp - @Jijidici - 14/01/2014
************************************************************************ */

#include "renderer/INKRenderable.h"

#include "renderer/shapes/INKSquareShape.h"

INKRenderable::INKRenderable(INKSquareShape* pShape)
	: _pShape(pShape) {

}

INKRenderable::~INKRenderable() {

}

void INKRenderable::render() {
	_pShape->draw();
}