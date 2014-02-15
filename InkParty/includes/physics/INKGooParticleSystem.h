/* ***********************************************************************
	INKGooParticleSystem.h - @Jijidici - 15/02/2014
************************************************************************ */

#ifndef __INK_GOO_PARTICLE_SYSTEM_H__
#define __INK_GOO_PARTICLE_SYSTEM_H__

#include <vector>
#include <utility>
#include "glm.hpp"
#include "physics/INKParticleSystem.h"
#include "physics/INKLink.h"

class INKGooParticleSystem : public INKParticleSystem {
public:
	INKGooParticleSystem(int iMaxCount, float fStandardMass, float fPartDist, float fDeltaDist);
	
	virtual void update(float fDt);
	void reset();

	bool addOneParticle(glm::vec3 position);

	std::vector<INKLink>& getGraph() { return _graph; }

protected:
	void init();

	float _fPartDist;
	float _fDeltaDist;
	std::vector<INKLink> _graph;
};

#endif
