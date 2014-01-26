/* ***********************************************************************
	INKGLProgram.h - @Jijidici - 09/01/2014
************************************************************************ */

#ifndef __INK_GL_PROGRAM_H__
#define __INK_GL_PROGRAM_H__

#include "GL/glew.h"
#include "glm.hpp"

class INKGLProgram {
public:
	static const GLchar* defaultVS;
	static const GLchar* defaultFS;

					INKGLProgram();
					~INKGLProgram();

	void			buildProgram(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource);
	void			use();
	void			updateUniforms();
	void			sendModelUniform(const glm::mat4& modelMatrix);

	const GLuint	getProgramID() { return _program; }

protected:
	void			initUniformLocations();

	GLuint	_program;
	GLint	_modelMatrixLocation;
	GLint	_viewMatrixLocation;
	GLint	_projectionMatrixLocation;
};

#endif //__INK_GL_PROGRAM_H__