/* ***********************************************************************
	INKAttractiveForce.h - @Jijidici - 08/02/2014
************************************************************************ */

#ifndef __INK_ATTRACTIVE_FORCE_H__
#define __INK_ATTRACTIVE_FORCE_H__

#include "glm.hpp"
#include "physics/forces/INKForce.h"
#include "physics/INKParticleSystem.h"

class INKAttractiveForce : public INKForce {
public:
					INKAttractiveForce(glm::vec3 attractionPoint, float fPower, float fBrakeCoef);
	virtual			~INKAttractiveForce();

	virtual void	apply(INKParticleSystem* pSystem);

protected:
	glm::vec3	_attractionPoint;
	float		_fPower;
	float		_fBrakeCoef;
};

#endif //__INK_ATTRACTIVE_FORCE_H__