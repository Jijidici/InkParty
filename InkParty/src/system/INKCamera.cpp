/* ***********************************************************************
	INKRenderer.cpp - @Jijidici - 14/01/2014
************************************************************************ */

#include "system/INKCamera.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

INKCamera::INKCamera(float fFrameRatio) {
	_position = glm::vec3(0.f, 0.f, 1.f);
	_matrixView = glm::lookAt(_position, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
	_matrixProj = glm::ortho(-10.f, 10.f, -10.f*fFrameRatio, 10.f*fFrameRatio);
}

INKCamera::~INKCamera() {

}

const glm::mat4 INKCamera::getView() {
	return glm::translate(_matrixView, _position);
}