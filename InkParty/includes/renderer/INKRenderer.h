/* ***********************************************************************
	INKRenderer.h - @Jijidici - 14/01/2014
************************************************************************ */

#ifndef __INK_RENDERER_H__
#define __INK_RENDERER_H__

#include <string>
#include <vector>
#include <map>
#include "GL/glew.h"
#include "renderer/INKGLProgram.h"
#include "renderer/shapes/INKSquareShape.h"
#include "system/INKCamera.h"
#include "physics/INKParticleSystem.h"

class INKRenderer {
public:
	static INKRenderer* getInstance();
	
	void			render();
	void			add(INKParticleSystem* pSystem);

	void			addShader(std::string sTag, const GLchar* vsSource, const GLchar* fsSource);
	INKGLProgram*	getShader(std::string sTag);

	INKSquareShape*	getSquare();

	void			setCurrentCamera(INKCamera* pCamera) { _pCurrentCamera = pCamera; }
	INKCamera*		getCurrentCamera() { return _pCurrentCamera; }

protected:
	INKRenderer();
	~INKRenderer();

	void			init();

	INKSquareShape* _pSquareModel;
	INKCamera* _pCurrentCamera;
	std::map<std::string, INKGLProgram*> _shadersMap;
	std::vector<INKParticleSystem*> _toRender;
};

#endif //__INK_RENDERER_H__