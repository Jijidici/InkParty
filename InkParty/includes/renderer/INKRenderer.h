/* ***********************************************************************
	INKRenderer.h - @Jijidici - 14/01/2014
************************************************************************ */

#ifndef __INK_RENDERER_H__
#define __INK_RENDERER_H__

#include <vector>

#include "renderer/INKRenderable.h"

class INKRenderer {
public:
	static INKRenderer* getInstance();
	
	void			init();
	void			render(std::vector<INKRenderable*>& toRender);

	INKSquareShape*	getSquare();

private:
	INKRenderer();
	~INKRenderer();

	INKSquareShape* _pSquareModel;
};

#endif //__INK_RENDERER_H__