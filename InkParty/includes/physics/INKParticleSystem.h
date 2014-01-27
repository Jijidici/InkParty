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

	void	addRandomParticles(int iParticleCount, float fAmplitude);
	void	addForce(INKForce* pForce) { _forcesToApply.push_back(pForce); }
	void	leapFrogSolve(float fDt);

	std::vector<INKParticle*>&	getParticles() { return _particles; }
	int							getParticlesCount() const { return _particles.size(); }
	INKRenderable*				getRenderableParticle(int iPartID) { return static_cast<INKRenderable*>(_particles[iPartID]); }

protected:
	std::vector<INKParticle*>	_particles;
	std::vector<INKForce*>		_forcesToApply;
};

#endif //__INK_PARTICLE_SYSTEM_H__