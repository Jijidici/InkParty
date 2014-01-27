/* ***********************************************************************
	INKPhysicSolid.h - @Jijidici - 27/01/2014
************************************************************************ */

#ifndef __INK_PHYSIC_SOLID_H__
#define __INK_PHYSIC_SOLID_H__

#include <vector>
#include "glm.hpp"
#include "renderer/INKRenderable.h"

class INKPhysicSolid : public INKRenderable {
public:
			INKPhysicSolid(std::vector<glm::vec3>& vertices);
			~INKPhysicSolid();

protected:
	std::vector<glm::vec3> _vertices;
};

#endif //__INK_PHYSIC_SOLID_H__