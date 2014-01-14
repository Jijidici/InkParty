/* ***********************************************************************
	INKSquareShape.cpp - @Jijidici - 14/01/2014
************************************************************************ */

#include "renderer/shapes/INKSquareShape.h"

#include "GL/glew.h"

#define POSITION_LOCATION 0

#define DIM_2D 2
#define SQUARE_VERTICES_COUNT 6

INKSquareShape::INKSquareShape()
	: _iVerticesCount(SQUARE_VERTICES_COUNT)
	, _iDim(DIM_2D)
	, _vbo(0)
	, _vao(0) {
	init();
}

INKSquareShape::~INKSquareShape() {
	glDeleteBuffers(1, &_vbo);
	glDeleteVertexArrays(1, &_vao);
}

void INKSquareShape::draw() {
	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, _iVerticesCount);
	glBindVertexArray(0);
}

void INKSquareShape::init() {
	GLfloat aVertices[] = { -0.5f,	-0.5f,
						  0.5f, 	-0.5f,
						  0.5f, 	0.5f,
						  0.5f, 	0.5f,
						  -0.5f,	0.5f,
						  -0.5f,	-0.5f };

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, SQUARE_VERTICES_COUNT*DIM_2D*sizeof(GLfloat), aVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	glEnableVertexAttribArray(POSITION_LOCATION);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glVertexAttribPointer(POSITION_LOCATION, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), reinterpret_cast<const GLvoid*>(0));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}