/* ***********************************************************************
	INKShape.h - @Jijidici - 27/01/2014
************************************************************************ */

#include "renderer/shapes/INKShape.h"

INKShape::INKShape() {
	_vao = 0;
	_vbo = 0;
}

INKShape::~INKShape() {
	glDeleteBuffers(1, &_vbo);
	glDeleteVertexArrays(1, &_vao);
}

void INKShape::draw() {
	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, _iVerticesCount);
	glBindVertexArray(0);
}