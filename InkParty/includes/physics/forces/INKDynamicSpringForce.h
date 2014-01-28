/* ***********************************************************************
	INKDynamicSpringForce.h - @Jijidici - 26/01/2014
************************************************************************ */

#ifndef __INK_DYNAMIC_SPRING_FORCE_H__
#define __INK_DYNAMIC_SPRING_FORCE_H__

#include "physics/INKParticle.h"

class INKDynamicSpringForce {
public:
	static INKDynamicSpringForce* getInstance();
	void apply(INKParticle* pP1, INKParticle* pP2, float fK, float fL, float fV, float fDt);

private:
	INKDynamicSpringForce();
};

#endif //__INK_DYNAMIC_SPRING_FORCE_H__