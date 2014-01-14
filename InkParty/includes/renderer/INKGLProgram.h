/* ***********************************************************************
	INKGLProgram.h - @Jijidici - 09/01/2014
************************************************************************ */

#ifndef __INK_GL_PROGRAM_H__
#define __INK_GL_PROGRAM_H__

#include "GL/glew.h"

class INKGLProgram {
public:
	static const GLchar* defaultVS;
	static const GLchar* defaultFS;

	INKGLProgram();
	~INKGLProgram();

	void buildProgram(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource);
	void use();

private:
	GLuint _program;
};

#endif //__INK_GL_PROGRAM_H__