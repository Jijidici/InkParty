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

	virtual void apply(INKParticleSystem* pSystem) = 0;
};

#endif // __INK_FORCE_H__