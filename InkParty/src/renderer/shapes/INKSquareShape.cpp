/* ***********************************************************************
	INKSquareShape.cpp - @Jijidici - 14/01/2014
************************************************************************ */

#include "renderer\shapes\INKSquareShape.h"

#include "GL/glew.h"

#define DIM_2D 2
#define SQUARE_VERTICES_COUNT 6

INKSquareShape::INKSquareShape()
	: _iVerticesCount(SQUARE_VERTICES_COUNT)
	, _iDim(DIM_2D)
	, _aVertices(nullptr) {
	init();
}

INKSquareShape::~INKSquareShape() {
	if(_aVertices != nullptr) {
		delete _aVertices;
		_aVertices = nullptr;
	}
}

void INKSquareShape::init() {
	_aVertices = new GLfloat[_iDim*_iVerticesCount];

	_aVertices[0]	= -0.5f;	_aVertices[1]	 = -0.5f;
	_aVertices[2]	= 0.5f;		_aVertices[3]	 = -0.5f;
	_aVertices[4]	= 0.5f;		_aVertices[5]	 = 0.5f;
	_aVertices[6]	= 0.5f;		_aVertices[7]	 = 0.5f;
	_aVertices[8]	= -0.5f;	_aVertices[9]	 = 0.5f;
	_aVertices[10]	= -0.5f;	_aVertices[11]	 = -0.5f;
}