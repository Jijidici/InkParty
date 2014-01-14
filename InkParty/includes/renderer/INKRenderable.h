/* ***********************************************************************
	INKRenderable.h - @Jijidici - 14/01/2014
************************************************************************ */

#ifndef __INK_RENDERABLE_H__
#define __INK_RENDERABLE_H__

#include "renderer/shapes/INKSquareShape.h"

class INKRenderable {
public:
	INKRenderable(INKSquareShape* pShape);
	~INKRenderable();

	void render();

private:
	INKSquareShape* _pShape;
};

#endif //__INK_RENDERABLE_H__