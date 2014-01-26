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
	
	void			render();
	void			add(INKRenderable* aRenderable);

	INKSquareShape*	getSquare();
	INKGLProgram*	getDefaultShaderProgram();

protected:
	INKRenderer();
	~INKRenderer();

	void			init();

	INKSquareShape* _pSquareModel;
	INKGLProgram*	_pDefaultShaderProgram;

	std::vector<INKRenderable*> _toRender;
};

#endif //__INK_RENDERER_H__