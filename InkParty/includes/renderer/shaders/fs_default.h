/* ***********************************************************************
	fs_default.h - @Jijidici - 14/01/2014
************************************************************************ */

#ifndef __FS_DEFAULT_H__
#define __FS_DEFAULT_H__

#ifndef GL_STRINGIFY
#define GL_STRINGIFY(s) #s
#endif

#include "GL/glew.h"

namespace inkshaders {

const GLchar* fs_default =
"#version 330 core\n"
GL_STRINGIFY(
	////BEGIN////

	out vec4 fragColor;

	void main() {
		fragColor = vec4(0., 0., 0., 1.);
	}

	////END////
);

}

#endif //__FS_DEFAULT_H__