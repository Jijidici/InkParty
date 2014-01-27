/* ***********************************************************************
	INKQuadTreeParticleSystem.cpp - @Jijidici - 27/01/2014
************************************************************************ */

#include "physics/INKQuadTreeParticleSystem.h"

#include <stdexcept>

INKQuadTreeParticleSystem::INKQuadTreeParticleSystem() {

}

INKQuadTreeParticleSystem::~INKQuadTreeParticleSystem() {

}

void INKQuadTreeParticleSystem::update(float fDt) {
	updateQuadTree();
	updateGraph();

	INKParticleSystem::update(fDt);
}

void INKQuadTreeParticleSystem::updateQuadTree() {
	_positionQuadTree.clear();

	QuadTreeNode root;
	root.center = glm::vec2(0.f);
	root.halfDimension = glm::vec2(10.f);

	tree<QuadTreeNode>::iterator itHead = _positionQuadTree.insert(_positionQuadTree.begin(), root);

	for(unsigned int i=0; i<_particles.size(); ++i) {
		if(!insertTreeNode(itHead, _particles[i]->getPosition(), i)) {
			throw std::runtime_error("Quadtree sorting : a particle is outside of the space");
		}
	}
}

void INKQuadTreeParticleSystem::updateGraph() {
	_graph.clear();
	
	//test
	for(unsigned int i=0; i<_particles.size()-1; ++i) {
		_graph.push_back(std::make_pair(i, i+1));
	}
	//test
}

bool INKQuadTreeParticleSystem::insertTreeNode(tree<QuadTreeNode>::iterator node, glm::vec3 particlePos, int particleId) {
	if(!contains(*node, particlePos)) {
		return false;
	}

	if(node->particleInfoMap.size() < QuadTreeNode::NODE_CAPACITY) {
		node->particleInfoMap.insert(std::make_pair(particleId, particlePos));
		return true;
	}

	if(tree<QuadTreeNode>::number_of_children(node) == 0) {
		subdivide(node);
	}

	for(tree<QuadTreeNode>::sibling_iterator it=_positionQuadTree.begin(node); it!=_positionQuadTree.end(node); ++it) {
		if(insertTreeNode(it, particlePos, particleId)) {
			return true;
		}
	}

	return false;
}

bool INKQuadTreeParticleSystem::contains(const QuadTreeNode& container, glm::vec3 particlePos) {
	if(particlePos.x > container.center.x - container.halfDimension.x && particlePos.x < container.center.x + container.halfDimension.x
	&& particlePos.y > container.center.y - container.halfDimension.y && particlePos.y < container.center.y + container.halfDimension.y) {
		return true;
	}

	return false;
}

void INKQuadTreeParticleSystem::subdivide(tree<QuadTreeNode>::iterator node) {
	QuadTreeNode northWest;
	QuadTreeNode northEast;
	QuadTreeNode southWest;
	QuadTreeNode southEast;

	northWest.center = glm::vec2(node->center.x - node->halfDimension.x/2.f, node->center.y + node->halfDimension.y/2.f);
	northEast.center = glm::vec2(node->center.x + node->halfDimension.x/2.f, node->center.y + node->halfDimension.y/2.f);
	southWest.center = glm::vec2(node->center.x - node->halfDimension.x/2.f, node->center.y - node->halfDimension.y/2.f);
	southEast.center = glm::vec2(node->center.x + node->halfDimension.x/2.f, node->center.y - node->halfDimension.y/2.f);
	northWest.halfDimension = node->halfDimension/2.f;
	northEast.halfDimension = node->halfDimension/2.f;
	southWest.halfDimension = node->halfDimension/2.f;
	southEast.halfDimension = node->halfDimension/2.f;

	tree<QuadTreeNode>::iterator itNW = _positionQuadTree.append_child(node, northWest);
	tree<QuadTreeNode>::iterator itNE = _positionQuadTree.append_child(node, northEast);
	tree<QuadTreeNode>::iterator itSW = _positionQuadTree.append_child(node, southWest);
	tree<QuadTreeNode>::iterator itSE = _positionQuadTree.append_child(node, southEast);

	for(std::map<int, glm::vec3>::iterator it=node->particleInfoMap.begin(); it!=node->particleInfoMap.end(); ++it) {
		if(!insertTreeNode(itNW, it->second, it->first)) {
			if(!insertTreeNode(itNE, it->second, it->first)) {
				if(!insertTreeNode(itSW, it->second, it->first))
					insertTreeNode(itSE, it->second, it->first);
			}
		}
	}
	node->particleInfoMap.clear();
}