/* ***********************************************************************
	INKSquareShape.h - @Jijidici - 14/01/2014
************************************************************************ */

#ifndef __INK_SQUARE_SHAPE_H__
#define __INK_SQUARE_SHAPE_H__

#include "GL/glew.h"

class INKSquareShape {
public:
	INKSquareShape();
	~INKSquareShape();

	void draw();

private:
	void init();

	int			_iVerticesCount;
	int			_iDim;
	GLuint		_vbo;
	GLuint		_vao;
};

#endif //__INK_SQUARE_SHAPE_H__