/* ***********************************************************************
	INKSquareShape.h - @Jijidici - 14/01/2014
************************************************************************ */

#ifndef __INK_SQUARE_SHAPE_H__
#define __INK_SQUARE_SHAPE_H__

#include "renderer/shapes/INKShape.h"

class INKSquareShape : public INKShape {
public:
					INKSquareShape();
	virtual			~INKSquareShape();

	virtual void	build();
};

#endif //__INK_SQUARE_SHAPE_H__