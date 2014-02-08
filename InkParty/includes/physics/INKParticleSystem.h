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
			INKParticleSystem(int iMaxCount, float fStandardMass);
	virtual	~INKParticleSystem();

	void			addParticles(int iParticleCount, float fMass);
	void			addSpawner(glm::vec3 spawnPoint) { _spawners.push_back(spawnPoint); }
	void			addWell(glm::vec3 wellPoint) { _wells.push_back(wellPoint); }
	void			addSolid(INKPhysicSolid* pSolid) { _solids.push_back(pSolid); }
	void			addForce(INKForce* pForce) { _forcesToApply.push_back(pForce); }
	virtual void	update(float fDt);

	glm::vec3						getPosition(int iPartId) { return _positions[iPartId]; }
	glm::vec3						getVelocity(int iPartId) { return _velocities[iPartId]; }
	glm::vec3						getForce(int iPartId) { return _forces[iPartId]; }
	float							getMass(int iPartId) { return _mass[iPartId]; }
	int								getParticleCount() const { return _iParticleCount; }
	std::vector<INKPhysicSolid*>&	getSolids() { return _solids; }
	int								getSolidsCount() const { return _solids.size(); }

	void							setMaxPartCount(int iCount) { _iMaxPartCount = iCount; }
	void							setStandardMass(float fMass) { _fStandardMass = fMass; }

	void							accumForce(int iPartId, glm::vec3 force) { _forces[iPartId] += force; }

protected:
	void						leapFrogSolve(float fDt);
	void						getNextState(int iPartId, glm::vec3& nextPos, glm::vec3& nextVel, float fDt);

	int								_iParticleCount;
	int								_iMaxPartCount;
	float							_fStandardMass;
	std::vector<glm::vec3>			_positions;
	std::vector<glm::vec3>			_velocities;
	std::vector<glm::vec3>			_forces;
	std::vector<float>				_mass;

	std::vector<glm::vec3>			_spawners;
	std::vector<glm::vec3>			_wells;
	std::vector<INKPhysicSolid*>	_solids;
	std::vector<INKForce*>			_forcesToApply;
};

#endif //__INK_PARTICLE_SYSTEM_H__