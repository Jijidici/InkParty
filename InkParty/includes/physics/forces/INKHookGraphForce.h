/* ***********************************************************************
	INKHookGraphForce.h - @Jijidici - 27/01/2014
************************************************************************ */

#ifndef __INK_HOOK_GRAPH_FORCE_H__
#define __INK_HOOK_GRAPH_FORCE_H__

#include "physics/forces/INKHookForce.h"
#include "physics/INKQuadTreeParticleSystem.h"

class INKHookGraphForce : public INKHookForce {
public:
					INKHookGraphForce(float fK, float fL);
	virtual			~INKHookGraphForce();

	virtual void	apply(INKQuadTreeParticleSystem* pSystem);
};

#endif //__INK_HOOK_GRAPH_FORCE_H__