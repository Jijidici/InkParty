/* ***********************************************************************
	INKDynamicSpringForce.h - @Jijidici - 26/01/2014
************************************************************************ */

#ifndef __INK_DYNAMIC_SPRING_FORCE_H__
#define __INK_DYNAMIC_SPRING_FORCE_H__

#include "physics/INKParticleSystem.h"

class INKDynamicSpringForce {
public:
	static INKDynamicSpringForce* getInstance();
	void apply(INKParticleSystem* pSystem, int iP1Id, int iP2Id, float fK, float fL, float fV, float fDt);

private:
	INKDynamicSpringForce();
};

#endif //__INK_DYNAMIC_SPRING_FORCE_H__