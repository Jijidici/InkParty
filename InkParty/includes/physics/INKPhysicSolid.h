/* ***********************************************************************
	INKPhysicSolid.h - @Jijidici - 27/01/2014
************************************************************************ */

#ifndef __INK_PHYSIC_SOLID_H__
#define __INK_PHYSIC_SOLID_H__

#include <vector>
#include "glm.hpp"
#include "renderer/INKRenderable.h"
#include "physics/INKParticle.h"

class INKPhysicSolid : public INKRenderable {
public:
			INKPhysicSolid(std::vector<glm::vec3>& vertices, float elasticity);
			~INKPhysicSolid();

	void	computeCollision(INKParticle* particle, glm::vec3 partNextPos, glm::vec3 partNextVel, float fDt);

	float	getElasticity() const { return _fElasticity; }
	void	setElasticity(float elasticity) { _fElasticity = elasticity; }

protected:
	bool	segmentIntersect(glm::vec2 A, glm::vec2 B, glm::vec2 p1, glm::vec2 p2, glm::vec2& intersection, glm::vec2& normale);

	std::vector<glm::vec3>	_vertices;
	float					_fElasticity;
};

#endif //__INK_PHYSIC_SOLID_H__