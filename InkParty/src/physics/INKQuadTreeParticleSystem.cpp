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
	//updateQuadTree();
	updateGraph();

	INKParticleSystem::update(fDt);
}

void INKQuadTreeParticleSystem::updateQuadTree() {
	_positionQuadTree.clear();

	QuadTreeNode root;
	root.center = glm::vec2(0.f);
	root.halfDimension = glm::vec2(100.f);

	tree<QuadTreeNode>::iterator itHead = _positionQuadTree.insert(_positionQuadTree.begin(), root);

	for(unsigned int i=0; i<_particles.size(); ++i) {
		if(!insertTreeNode(itHead, _particles[i]->getPosition(), i)) {
			//throw std::runtime_error("Quadtree sorting : a particle is outside of the space");
		}
	}
}

void INKQuadTreeParticleSystem::updateGraph() {
	_graph.clear();
	
	for(unsigned int i=0; i<_particles.size(); ++i) {
		for(unsigned int j=i+1; j<_particles.size(); ++j) {
			float d = glm::distance(_particles[i]->getPosition(), _particles[j]->getPosition());
			if(d < 2.f*_particles[i]->getMass()) {
				_graph.push_back(std::make_pair(i, j));
			}
		}

		/*std::vector<int> nearestParticleId = getNearestParticules(++_positionQuadTree.begin(), _particles[i]->getPosition(), 2.f*_particles[i]->getMass());

		for(std::vector<int>::iterator itId=nearestParticleId.begin(); itId!=nearestParticleId.end(); ++itId) {
			if(i != *itId) {
				_graph.push_back(std::make_pair(i, *itId));
			}
		}*/
	}
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

bool INKQuadTreeParticleSystem::contains(const QuadTreeNode& container, glm::vec3 particlePos, float fRange) {
	if((particlePos.x-fRange > container.center.x - container.halfDimension.x && particlePos.x-fRange < container.center.x + container.halfDimension.x
	&& particlePos.y-fRange > container.center.y - container.halfDimension.y && particlePos.y-fRange < container.center.y + container.halfDimension.y) ||
	(particlePos.x+fRange > container.center.x - container.halfDimension.x && particlePos.x+fRange < container.center.x + container.halfDimension.x
	&& particlePos.y-fRange > container.center.y - container.halfDimension.y && particlePos.y-fRange < container.center.y + container.halfDimension.y) ||
	(particlePos.x-fRange > container.center.x - container.halfDimension.x && particlePos.x-fRange < container.center.x + container.halfDimension.x
	&& particlePos.y+fRange > container.center.y - container.halfDimension.y && particlePos.y+fRange < container.center.y + container.halfDimension.y) ||
	(particlePos.x+fRange > container.center.x - container.halfDimension.x && particlePos.x+fRange < container.center.x + container.halfDimension.x
	&& particlePos.y+fRange > container.center.y - container.halfDimension.y && particlePos.y+fRange < container.center.y + container.halfDimension.y)) {
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

std::vector<int> INKQuadTreeParticleSystem::getNearestParticules(tree<QuadTreeNode>::iterator node, glm::vec3 particlePos, float fRange) {
	std::vector<int> vecIds;

	if(!contains(*node, particlePos, fRange)) {
		return vecIds;
	}

	QuadTreeNode tempAABB;
	tempAABB.center = glm::vec2(particlePos.x, particlePos.y);
	tempAABB.halfDimension = glm::vec2(fRange);

	for(std::map<int, glm::vec3>::iterator it=node->particleInfoMap.begin(); it!=node->particleInfoMap.end(); ++it) {
		if(contains(tempAABB, it->second)) {
			vecIds.push_back(it->first);
		}
	}

	for(tree<QuadTreeNode>::sibling_iterator itChild=_positionQuadTree.begin(node); itChild!=_positionQuadTree.end(node); ++itChild) {
		std::vector<int> tmpVecIds = getNearestParticules(itChild, particlePos, fRange);
		for(std::vector<int>::iterator it=tmpVecIds.begin(); it!=tmpVecIds.end(); ++it) {
			vecIds.push_back(*it);
		}
	}

	return vecIds;
}