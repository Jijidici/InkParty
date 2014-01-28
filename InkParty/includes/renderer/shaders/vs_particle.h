/* ***********************************************************************
	vs_particle.h - @Jijidici - 14/01/2014
************************************************************************ */

#ifndef __VS_PARTICLE_H__
#define __VS_PARTICLE_H__

#ifndef GL_STRINGIFY
#define GL_STRINGIFY(s) #s
#endif

#include "GL/glew.h"

namespace inkshaders {

const GLchar* vs_particle =
"#version 330 core\n"
GL_STRINGIFY(
	////BEGIN////

    layout(location = 0) in vec3 vPosition;
	
	uniform mat4 uModelMat = mat4(1.);
	uniform mat4 uViewMat = mat4(1.);
	uniform mat4 uProjMat = mat4(1.);

	out vec3 fPosition;
	out vec3 fAbsolutePosition;

    void main() {
        gl_Position = uProjMat * uViewMat * uModelMat * vec4(vPosition, 1.);
		fPosition = vPosition;
		fAbsolutePosition = (uModelMat * vec4(vPosition, 1.)).xyz;
    }

	///END///
);

}

#endif //__VS_PARTICLE_H__