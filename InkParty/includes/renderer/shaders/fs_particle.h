/* ***********************************************************************
	fs_particle.h - @Jijidici - 14/01/2014
************************************************************************ */

#ifndef __FS_PARTICLE_H__
#define __FS_PARTICLE_H__

#ifndef GL_STRINGIFY
#define GL_STRINGIFY(s) #s
#endif

#include "GL/glew.h"

namespace inkshaders {

const GLchar* fs_particle =
"#version 330 core\n"
GL_STRINGIFY(
	////BEGIN////

	in vec3 fPosition;
	out vec3 fAbsolutePosition;

	out vec4 fragColor;

	void main() {
		float alpha = 0.f;
		float d = length(fPosition);
		if(d<0.5) {
			alpha = 1.f;
		}

		float colorCoef = (fAbsolutePosition.y + 10.)/20.;
		fragColor = vec4(1., 0.5, 0., alpha);
	}

	////END////
);

}

#endif //__FS_PARTICLE_H__