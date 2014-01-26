/* ***********************************************************************
	INKParticle.h - @Jijidici - 26/01/2014
************************************************************************ */

#ifndef __INK_PARTICLE_H__
#define __INK_PARTICLE_H__

#include "renderer/INKRenderable.h"

#include "glm.hpp"

class INKParticle : public INKRenderable {
public:
	INKParticle();
	~INKParticle();

	const glm::vec3	getVelocity() const { return _velocity; }
	const glm::vec3 getForce() const { return _force; }
	const float		getMass() const { return _fMass; }

	void			setVelocity(glm::vec3 velocity) { _velocity = velocity; }
	void			setForce(glm::vec3 force) { _force = force; }
	void			addForce(glm::vec3 force) { _force += force; }
	void			setMass(float fMass);

protected:
	glm::vec3	_velocity;
	glm::vec3	_force;
	float		_fMass;
};

#endif //__INK_PARTICLE_H__