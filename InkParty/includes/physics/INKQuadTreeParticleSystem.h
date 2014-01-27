/* ***********************************************************************
	INKQuadTreeParticleSystem.h - @Jijidici - 27/01/2014
************************************************************************ */

#ifndef __INK_QUADTREE_PARTICLE_SYSTEM_H__
#define __INK_QUADTREE_PARTICLE_SYSTEM_H__

#include <vector>
#include <utility>
#include <map>
#include "tree.hh"
#include "glm.hpp"
#include "physics/INKParticleSystem.h"

typedef std::vector<std::pair<int, int>> TParticleGraph;

class INKQuadTreeParticleSystem : public INKParticleSystem {
public:
					INKQuadTreeParticleSystem();
	virtual			~INKQuadTreeParticleSystem();

	virtual void	update(float fDt);

	TParticleGraph&	getGraph() { return _graph; }

protected:
	struct QuadTreeNode {
		static const int NODE_CAPACITY = 4;

		glm::vec2 center;
		glm::vec2 halfDimension;
		std::map<int, glm::vec3> particleInfoMap;
	};

	void	updateQuadTree();
	void	updateGraph();

	bool				insertTreeNode(tree<QuadTreeNode>::iterator node, glm::vec3 particlePos, int particleId);
	bool				contains(const QuadTreeNode& container, glm::vec3 particlePos);
	bool				contains(const QuadTreeNode& container, glm::vec3 particlePos, float fRange);
	void				subdivide(tree<QuadTreeNode>::iterator node);
	std::vector<int>	getNearestParticules(tree<QuadTreeNode>::iterator node, glm::vec3 particulePos, float fRange);

	tree<QuadTreeNode>	_positionQuadTree;
	TParticleGraph		_graph;
};

#endif //__INK_QUADTREE_PARTICLE_SYSTEM_H__