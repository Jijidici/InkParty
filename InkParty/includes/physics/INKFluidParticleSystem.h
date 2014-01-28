/* ***********************************************************************
	INKFluidParticleSystem.h - @Jijidici - 28/01/2014
************************************************************************ */

#ifndef __INK_FLUID_PARTICLE_SYSTEM_H__
#define __INK_FLUID_PARTICLE_SYSTEM_H__

#include <vector>
#include "physics/INKParticleSystem.h"

class INKFluidParticleSystem : public INKParticleSystem {
public:
	INKFluidParticleSystem(int iSpaceWidth, int iSpaceHeight, int iCellSize);
	~INKFluidParticleSystem();

	virtual void	update(float fDt);

	void	setSpringRigidity(float fRepulsiveRigidity, float fAttractiveRigidity) { _fRepulsiveSpringRigidity = fRepulsiveRigidity; _fAttractiveSpringRigidity = fAttractiveRigidity; }
	void	setSpringLengths(float fRepulsiveLength, float fAttractiveLength) { _fRepulsiveSpringLength = fRepulsiveLength; _fAttractiveSpringLength = fAttractiveLength; }
	void	setBrakeCoef(float fCoef) { _fBrakeCoef = fCoef; }
	void	setInfluenceDelta(float fDelta) { _fInfluenceDelta = fDelta; }

protected:
	float	_fRepulsiveSpringRigidity;
	float	_fAttractiveSpringRigidity;
	float	_fRepulsiveSpringLength;
	float	_fAttractiveSpringLength;
	float	_fBrakeCoef;
	float	_fInfluenceDelta;

	int		_iSpaceW;
	int		_iSpaceH;
	int		_iCellSize;
	int		_iCellInWidthCount;
	int		_iCellInHeightCount;
	std::vector<std::vector<int>> _grid;
};

#endif //__INK_FLUID_PARTICLE_SYSTEM_H__