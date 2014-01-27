/* ***********************************************************************
	INKCustomShape.cpp - @Jijidici - 27/01/2014
************************************************************************ */

#include "renderer/shapes/INKCustomShape.h"

#include "GL/glew.h"

#define POSITION_LOCATION 0

INKCustomShape::INKCustomShape()
	: INKShape() {
	_iVerticesCount = 0;
	_buildType = eFan;
}

INKCustomShape::~INKCustomShape(){

}

void INKCustomShape::build() {
	_iVerticesCount = _vertices.size();

	if(_vbo == 0) {
		glGenBuffers(1, &_vbo);
	}
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _iVerticesCount*3*sizeof(GLfloat), &(_vertices[0]), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if(_vao == 0) {
		glGenVertexArrays(1, &_vao);
	}
	glBindVertexArray(_vao);
	glEnableVertexAttribArray(POSITION_LOCATION);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), reinterpret_cast<const GLvoid*>(0));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void INKCustomShape::draw() {
	glBindVertexArray(_vao);
	if(_buildType == eFan) {
		glDrawArrays(GL_TRIANGLE_FAN, 0, _iVerticesCount);
	} else {
		glDrawArrays(GL_TRIANGLE_STRIP, 0, _iVerticesCount);
	}
	glBindVertexArray(0);
}