/* ***********************************************************************
	INKPartyParticleSystem.h - @Jijidici - 11/02/2014
************************************************************************ */

#ifndef __INK_PARTY_PARTICLE_SYSTEM__
#define __INK_PARTY_PARTICLE_SYSTEM__

#include "physics/INKFluidParticleSystem.h"

class INKPartyParticleSystem : public INKFluidParticleSystem {
public:
	INKPartyParticleSystem();

	void init();
	void update(float fDt);

	void rotateUpperHexagon(float fAngle) { _hexagons[1]->setAngle(fAngle); };
};

#endif //__INK_PARTY_PARTICLE_SYSTEM__
