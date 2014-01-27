/* ***********************************************************************
	INKConstantForce.h - @Jijidici - 27/01/2014
************************************************************************ */

#ifndef __INK_CONSTANT_FORCE_H__
#define __INK_CONSTANT_FORCE_H__

#include "glm.hpp"
#include "physics/forces/INKForce.h"
#include "physics/INKParticleSystem.h"

class INKConstantForce : public INKForce {
public:
					INKConstantForce(glm::vec3 initialForce);
	virtual			~INKConstantForce();

	virtual void	apply(INKParticleSystem* pSystem);

protected:
	glm::vec3		_force;
};

#endif //__INK_CONSTANT_FORCE_H__