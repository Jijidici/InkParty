/* ***********************************************************************
	INKBrakeGraphForce.h - @Jijidici - 27/01/2014
************************************************************************ */

#ifndef __INK_BRAKE_GRAPH_FORCE_H__
#define __INK_BRAKE_GRAPH_FORCE_H__

#include "physics/forces/INKBrakeForce.h"
#include "physics/INKQuadTreeParticleSystem.h"

class INKBrakeGraphForce : public INKBrakeForce {
public:
					INKBrakeGraphForce(float fV);
	virtual			~INKBrakeGraphForce();

	virtual void	apply(INKQuadTreeParticleSystem* pSystem);
};

#endif //__INK_BRAKE_GRAPH_FORCE_H__