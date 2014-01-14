/* ***********************************************************************
	INKRenderer.h - @Jijidici - 14/01/2014
************************************************************************ */

#ifndef __INK_RENDERER_H__
#define __INK_RENDERER_H__

#include <vector>

#include "renderer/INKRenderable.h"
#include "renderer/INKGLProgram.h"

class INKRenderer {
public:
	static INKRenderer* getInstance();
	
	void			init();
	void			render(std::vector<INKRenderable*>& toRender);

	INKSquareShape*	getSquare();

	INKGLProgram*	getDefaultShaderProgram();

private:
	INKRenderer();
	~INKRenderer();

	INKSquareShape* _pSquareModel;

	INKGLProgram*	_pDefaultShaderProgram;
};

#endif //__INK_RENDERER_H__