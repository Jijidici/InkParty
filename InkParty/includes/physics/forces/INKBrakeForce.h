/* ***********************************************************************
	INKBrakeForce.h - @Jijidici - 27/01/2014
************************************************************************ */

#ifndef __INK_BRAKE_FORCE_H__
#define __INK_BRAKE_FORCE_H__

#include "physics/forces/INKForce.h"

class INKBrakeForce : public INKForce {
public:
					INKBrakeForce(float fV);
	virtual			~INKBrakeForce();

	virtual void	apply(INKParticleSystem* pSystem);

protected:
	float	_fV;
};

#endif //__INK_BRAKE_FORCE_H__