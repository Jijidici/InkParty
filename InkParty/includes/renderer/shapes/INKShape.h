/* ***********************************************************************
	INKShape.h - @Jijidici - 27/01/2014
************************************************************************ */

#ifndef __INK_SHAPE_H__
#define __INK_SHAPE_H__

#include "GL/glew.h"

class INKShape {
public:
					INKShape();
	virtual			~INKShape();

	virtual void	build() = 0;
	void			draw();

protected:
	int		_iVerticesCount;
	GLuint	_vbo;
	GLuint	_vao;
};

#endif //__INK_SHAPE_H__