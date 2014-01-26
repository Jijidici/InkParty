/* ***********************************************************************
	INKParticleSystem.h - @Jijidici - 26/01/2014
************************************************************************ */

#ifndef __INK_PARTICLE_SYSTEM_H__
#define __INK_PARTICLE_SYSTEM_H__

#include <vector>
#include "physics/INKParticle.h"
#include "physics/forces/INKForce.h"

class INKParticleSystem {
public:
			INKParticleSystem();
			~INKParticleSystem();

	void	addRandomParticles(int iParticleCount, int amplitude);
	void	addForce(INKForce* pForce) { _forcesToApply.push_back(pForce); }

	const std::vector<INKParticle*>	getParticles() const { return _particles; }

protected:
	std::vector<INKParticle*>	_particles;
	std::vector<INKForce*>		_forcesToApply;
};

#endif //__INK_PARTICLE_SYSTEM_H__