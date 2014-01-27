/* ***********************************************************************
	INKSquareShape.cpp - @Jijidici - 14/01/2014
************************************************************************ */

#include "renderer/shapes/INKSquareShape.h"

#include "GL/glew.h"

#define POSITION_LOCATION 0

#define SQUARE_VERTICES_COUNT 6

INKSquareShape::INKSquareShape()
	: INKShape() {
	_iVerticesCount = SQUARE_VERTICES_COUNT;
	build();
}

INKSquareShape::~INKSquareShape() {
	
}

void INKSquareShape::build() {
	GLfloat aVertices[] = { -0.5f,	-0.5f,	0.f,
						  0.5f, 	-0.5f,	0.f,
						  0.5f, 	0.5f,	0.f,
						  0.5f, 	0.5f,	0.f,
						  -0.5f,	0.5f,	0.f,
						  -0.5f,	-0.5f,	0.f };

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _iVerticesCount*3*sizeof(GLfloat), aVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	glEnableVertexAttribArray(POSITION_LOCATION);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), reinterpret_cast<const GLvoid*>(0));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}