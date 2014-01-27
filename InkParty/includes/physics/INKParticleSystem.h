/* ***********************************************************************
	INKParticleSystem.h - @Jijidici - 26/01/2014
************************************************************************ */

#ifndef __INK_PARTICLE_SYSTEM_H__
#define __INK_PARTICLE_SYSTEM_H__

#include <vector>
#include "physics/INKParticle.h"
#include "physics/INKPhysicSolid.h"
#include "physics/forces/INKForce.h"

class INKParticleSystem {
public:
			INKParticleSystem();
	virtual	~INKParticleSystem();

	void	addRandomParticles(int iParticleCount, float fAmplitude);
	void	addParticles(int iParticleCount, float fMass);
	void	addSolid(INKPhysicSolid* pSolid) { _solids.push_back(pSolid); }
	void	addForce(INKForce* pForce) { _forcesToApply.push_back(pForce); }
	void	update(float fDt);

	std::vector<INKParticle*>&		getParticles() { return _particles; }
	INKParticle*					getParticle(int id) { return _particles[id]; }
	int								getParticlesCount() const { return _particles.size(); }
	std::vector<INKPhysicSolid*>&	getSolids() { return _solids; }
	int								getSolidsCount() const { return _solids.size(); }

protected:
	void						leapFrogSolve(float fDt);
	void						getNextState(INKParticle* pParticle, glm::vec3& nextPos, glm::vec3& nextVel, float fDt);

	std::vector<INKParticle*>		_particles;
	std::vector<INKPhysicSolid*>	_solids;
	std::vector<INKForce*>			_forcesToApply;
};

#endif //__INK_PARTICLE_SYSTEM_H__