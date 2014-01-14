/* ***********************************************************************
	INKSquareShape.h - @Jijidici - 14/01/2014
************************************************************************ */

#ifndef __INK_SQUARE_SHAPE_H__
#define __INK_SQUARE_SHAPE_H__

#include "GL\glew.h"

class INKSquareShape {
public:
	INKSquareShape();
	~INKSquareShape();

	inline int		getVerticesCount() { return _iVerticesCount; }
	inline int		getDim() { return _iDim; }
	inline GLfloat*	getVertices() { return _aVertices; }

private:
	void init();

	int			_iVerticesCount;
	int			_iDim;
	GLfloat*	_aVertices;
};

#endif //__INK_SQUARE_SHAPE_H__