/* ***********************************************************************
	vs_default.h - @Jijidici - 14/01/2014
************************************************************************ */

#ifndef __VS_DEFAULT_H__
#define __VS_DEFAULT_H__

#ifndef GL_STRINGIFY
#define GL_STRINGIFY(s) #s
#endif

#include "GL/glew.h"

namespace inkshaders {

const GLchar* vs_default =
"#version 330 core\n"
GL_STRINGIFY(
	////BEGIN////

    layout(location = 0) in vec3 vPosition;
	
	uniform mat4 uModelMat = mat4(1.);
	uniform mat4 uViewMat = mat4(1.);
	uniform mat4 uProjMat = mat4(1.);

    void main() {
        gl_Position = uProjMat * uViewMat * uModelMat * vec4(vPosition, 1.);
    }

	///END///
);

}

#endif //__VS_DEFAULT_H__