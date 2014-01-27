/* ***********************************************************************
	INKQuadTreeParticleSystem.h - @Jijidici - 27/01/2014
************************************************************************ */

#ifndef __INK_QUADTREE_PARTICLE_SYSTEM_H__
#define __INK_QUADTREE_PARTICLE_SYSTEM_H__

#include <vector>
#include <utility>
#include "tree.hh"
#include "glm.hpp"
#include "physics/INKParticleSystem.h"

typedef std::vector<std::pair<int, int>> TParticleGraph;

class INKQuadTreeParticleSystem : public INKParticleSystem {
public:
					INKQuadTreeParticleSystem();
	virtual			~INKQuadTreeParticleSystem();

	TParticleGraph&	getGraph() { return _graph; }

protected:
	struct QuadTreeNode {
		static const int NODE_CAPACITY = 4;

		glm::vec2 center;
		glm::vec2 halfDimension;
		std::vector<int> particlesIds;
	};

	tree<QuadTreeNode>	_positionQuadTree;
	TParticleGraph		_graph;
};

#endif //__INK_QUADTREE_PARTICLE_SYSTEM_H__