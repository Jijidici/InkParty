/* ***********************************************************************
	INKCamera.h - @Jijidici - 26/01/2014
************************************************************************ */

#ifndef __INK_CAMERA_H__
#define __INK_CAMERA_H__

#include "glm.hpp"
#include "math/INKMatrixStack.h"

class INKCamera {
public:
	INKCamera(float fFrameRatio);
	~INKCamera();

	const glm::mat4 getProjection() { return _matrixProj; }
	const glm::mat4 getView();

	const glm::vec3 getPosition() { return _position; }
	void setPosition(glm::vec3 position) { _position = position; }

protected:
	glm::mat4 _matrixProj;
	glm::mat4 _matrixView;
	glm::vec3 _position;
};

#endif //__INK_CAMERA_H__