/* ***********************************************************************
	INKGooParticleSystem.cpp - @Jijidici - 15/02/2014
************************************************************************ */

#include "physics/INKGooParticleSystem.h"
#include "physics/INKPhysicSolid.h"
#include "physics/forces/INKConstantForce.h"
#include "physics/forces/INKDynamicSpringForce.h"

INKGooParticleSystem::INKGooParticleSystem(int iMaxCount, float fStandardMass, float fPartDist, float fDeltaDist)
	: INKParticleSystem(iMaxCount, fStandardMass)
	, _fPartDist(fPartDist)
	, _fDeltaDist(fDeltaDist) {
	init();
}

void INKGooParticleSystem::update(float fDt) {
	for(std::vector<INKLink>::iterator it=_graph.begin(); it!=_graph.end(); ++it) {
		INKDynamicSpringForce::getInstance()->apply(this, it->getP1Id(), it->getP2Id(), 10.f, it->getLength(), 0.01f, fDt);
	}

	INKParticleSystem::update(fDt);
}

bool INKGooParticleSystem::addOneParticle(glm::vec3 position) {
	bool bToAdd = false;

	//first particles
	if(_iParticleCount == 0) {
		bToAdd = true;
	} else {
		std::vector<INKLink> toAddLinks;
		for(int i=0; i<_iParticleCount; ++i) {
			float fFromPartDist = glm::distance(position, _positions[i]);
			if(fFromPartDist <= _fPartDist+_fDeltaDist) {
				INKLink newLink(i, _iParticleCount, fFromPartDist);
				toAddLinks.push_back(newLink);
			}
		}

		if(toAddLinks.size() >= 2 || _iParticleCount < 3) {
			for(std::vector<INKLink>::iterator it=toAddLinks.begin(); it!=toAddLinks.end(); ++it) {
				_graph.push_back(*it);
			}
			bToAdd = true;
		}
	}

	if(bToAdd) {
		_positions.push_back(position);
		_velocities.push_back(glm::vec3(0.f));
		_forces.push_back(glm::vec3(0.f));
		_mass.push_back(_fStandardMass);
		++_iParticleCount;
	}

	return bToAdd;
}

void INKGooParticleSystem::init() {
	this->addForce(new INKConstantForce(glm::vec3(0.f, -3.f, 0.f)));
	
	std::vector<glm::vec3> groundVertex;
	groundVertex.push_back(glm::vec3(-10.f, -9.f, 0.f));
	groundVertex.push_back(glm::vec3( 10.f, -9.f, 0.f));
	groundVertex.push_back(glm::vec3( 10.f, -10.f, 0.f));
	groundVertex.push_back(glm::vec3(-10.f, -10.f, 0.f));

	this->addSolid(new INKPhysicSolid(groundVertex, 1.f));

	// initial particles
	this->addOneParticle(glm::vec3(-_fPartDist/2.f, -8.5f, 0.f));
	this->addOneParticle(glm::vec3(_fPartDist/2.f, -8.5f, 0.f));
	this->addOneParticle(glm::vec3(0.f, -8.5f+(_fPartDist*0.86602540378f), 0.f));
}