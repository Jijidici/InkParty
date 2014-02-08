/* ***********************************************************************
	fs_well.h - @Jijidici - 08/02/2014
************************************************************************ */

#ifndef __FS_WELL_H__
#define __FS_WELL_H__

#ifndef GL_STRINGIFY
#define GL_STRINGIFY(s) #s
#endif

#include "GL/glew.h"

namespace inkshaders {

const GLchar* fs_well =
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
		fragColor = vec4(0., 0.5, 1., alpha);
	}

	////END////
);

}

#endif //__FS_WELL_H__