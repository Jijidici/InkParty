/* ***********************************************************************
	INKRenderable.h - @Jijidici - 14/01/2014
************************************************************************ */

#ifndef __INK_RENDERABLE_H__
#define __INK_RENDERABLE_H__

#include "glm.hpp"
#include "renderer/shapes/INKSquareShape.h"
#include "renderer/INKGLProgram.h"

class INKRenderable {
public:
					INKRenderable(INKSquareShape* pShape);
					~INKRenderable();

	void			render();

	const glm::vec3	getPosition() const { return _position; }
	const glm::vec3	getScale() const { return _scale; }
	const float		getRotation() const { return _fRotation; }

	void			setPosition(glm::vec3 position) { _position = position; }
	void			setScale(glm::vec3 scale) { _scale = scale; }
	void			setRotation(float fRotation) { _fRotation = fRotation; }

private:
	glm::vec3		_position;
	glm::vec3		_scale;
	float			_fRotation;

	INKSquareShape* _pShape;
	INKGLProgram*	_pProgram;
};

#endif //__INK_RENDERABLE_H__