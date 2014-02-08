/* ***********************************************************************
	INKPhysicSolid.h - @Jijidici - 27/01/2014
************************************************************************ */

#ifndef __INK_PHYSIC_SOLID_H__
#define __INK_PHYSIC_SOLID_H__

#include <vector>
#include "glm.hpp"
#include "renderer/shapes/INKCustomShape.h"
#include "physics/INKParticle.h"

class INKPhysicSolid {
public:
			INKPhysicSolid(std::vector<glm::vec3>& vertices, float elasticity);
			~INKPhysicSolid();

	void	computeCollision(glm::vec3 partPos, float fPartMass, glm::vec3 partNextPos, glm::vec3 partNextVel, float fDt, glm::vec3& partForce);

	float	getElasticity() const { return _fElasticity; }
	void	setElasticity(float elasticity) { _fElasticity = elasticity; }

	INKCustomShape*	getShape() { return _pShape; }

protected:
	bool	segmentIntersect(glm::vec2 A, glm::vec2 B, glm::vec2 p1, glm::vec2 p2, glm::vec2& intersection, glm::vec2& normale);

	std::vector<glm::vec3>	_vertices;
	float					_fElasticity;
	INKCustomShape*			_pShape;
};

#endif //__INK_PHYSIC_SOLID_H__