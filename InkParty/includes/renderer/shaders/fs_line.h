/* ***********************************************************************
	fs_line.h - @Jijidici - 15/02/2014
************************************************************************ */

#ifndef __FS_LINE_H__
#define __FS_LINE_H__

#ifndef GL_STRINGIFY
#define GL_STRINGIFY(s) #s
#endif

#include "GL/glew.h"

namespace inkshaders {

const GLchar* fs_line =
"#version 330 core\n"
GL_STRINGIFY(
	////BEGIN////

	out vec4 fragColor;

	void main() {
		fragColor = vec4(0., 1., 1., 1.);
	}

	////END////
);

}

#endif //__FS_LINE_H__