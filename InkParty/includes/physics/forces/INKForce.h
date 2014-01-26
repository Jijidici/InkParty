/* ***********************************************************************
	INKForce.h - @Jijidici - 26/01/2014
************************************************************************ */

#ifndef __INK_FORCE_H__
#define __INK_FORCE_H__

class INKParticleSystem;

class INKForce {
public:
	INKForce();
	virtual ~INKForce();

	virtual void apply(INKParticleSystem& system) = 0;
};

#endif