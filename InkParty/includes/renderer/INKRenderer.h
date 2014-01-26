/* ***********************************************************************
	INKRenderer.h - @Jijidici - 14/01/2014
************************************************************************ */

#ifndef __INK_RENDERER_H__
#define __INK_RENDERER_H__

#include <vector>

#include "renderer/INKRenderable.h"
#include "renderer/INKGLProgram.h"
#include "system/INKCamera.h"

class INKRenderer {
public:
	static INKRenderer* getInstance();
	
	void			render();
	void			add(INKRenderable* aRenderable);
	void			add(std::vector<INKRenderable*> renderables);

	INKSquareShape*	getSquare();
	INKGLProgram*	getDefaultShaderProgram();

	void			setCurrentCamera(INKCamera* pCamera) { _pCurrentCamera = pCamera; }
	INKCamera*		getCurrentCamera() { return _pCurrentCamera; }

protected:
	INKRenderer();
	~INKRenderer();

	void			init();

	INKSquareShape* _pSquareModel;
	INKGLProgram*	_pDefaultShaderProgram;

	std::vector<INKRenderable*> _toRender;

	INKCamera* _pCurrentCamera;
};

#endif //__INK_RENDERER_H__