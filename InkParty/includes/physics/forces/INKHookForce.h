/* ***********************************************************************
	INKHookForce.h - @Jijidici - 27/01/2014
************************************************************************ */

#ifndef __INK_HOOK_FORCE_H__
#define __INK_HOOK_FORCE_H__

#include "physics/forces/INKForce.h"

class INKHookForce : public INKForce {
public:
					INKHookForce(float fK, float fL);
	virtual			~INKHookForce();

	virtual void	apply(INKParticleSystem* pSystem);

protected:
	float	_fK;
	float	_fL;
};

#endif //__INK_HOOK_FORCE_H__