/* ***********************************************************************
	INKPhysicSolid.cpp - @Jijidici - 27/01/2014
************************************************************************ */

#include "physics/INKPhysicSolid.h"

#include "renderer/shapes/INKCustomShape.h"

INKPhysicSolid::INKPhysicSolid(std::vector<glm::vec3>& vertices)
	: INKRenderable(new INKCustomShape())
	, _vertices() {
	INKCustomShape* pCastCustomShape = static_cast<INKCustomShape*>(_pShape);

	for(std::vector<glm::vec3>::iterator it=vertices.begin(); it!=vertices.end(); ++it) {
		_vertices.push_back(*it);
		pCastCustomShape->addPoint(*it);
	}
	pCastCustomShape->setBuildType(INKCustomShape::eStrip);
	pCastCustomShape->build();
}

INKPhysicSolid::~INKPhysicSolid() {

}