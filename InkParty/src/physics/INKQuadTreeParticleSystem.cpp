/* ***********************************************************************
	INKQuadTreeParticleSystem.cpp - @Jijidici - 27/01/2014
************************************************************************ */

#include "physics/INKQuadTreeParticleSystem.h"

INKQuadTreeParticleSystem::INKQuadTreeParticleSystem() {

}

INKQuadTreeParticleSystem::~INKQuadTreeParticleSystem() {

}

void INKQuadTreeParticleSystem::update(float fDt) {
	updateGraph();

	INKParticleSystem::update(fDt);
}

void INKQuadTreeParticleSystem::updateGraph() {
	_graph.clear();
	
	//test
	for(unsigned int i=0; i<_particles.size()-1; ++i) {
		_graph.push_back(std::make_pair(i, i+1));
	}
	//test
}

