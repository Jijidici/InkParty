/* ***********************************************************************
	INKFluidParticleSystem.h - @Jijidici - 28/01/2014
************************************************************************ */

#ifndef __INK_FLUID_PARTICLE_SYSTEM_H__
#define __INK_FLUID_PARTICLE_SYSTEM_H__

#include "physics/INKParticleSystem.h"

class INKFluidParticleSystem : public INKParticleSystem {
public:
	INKFluidParticleSystem();
	~INKFluidParticleSystem();

	virtual void	update(float fDt);

	void	setSpringRigidity(float fRigidity) { _fSpringRigidity = fRigidity; }
	void	setSpringLengths(float fRepulsiveLength, float fAttractiveLength) { _fRepulsiveSpringLength = fRepulsiveLength; _fAttractiveSpringLength = fAttractiveLength; }
	void	setBrakeCoef(float fCoef) { _fBrakeCoef = fCoef; }
	void	setInfluenceDelta(float fDelta) { _fInfluenceDelta = fDelta; }

protected:
	float	_fSpringRigidity;
	float	_fRepulsiveSpringLength;
	float	_fAttractiveSpringLength;
	float	_fBrakeCoef;
	float	_fInfluenceDelta;
};

#endif //__INK_FLUID_PARTICLE_SYSTEM_H__