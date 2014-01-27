/* ***********************************************************************
	INKPhysicSolid.cpp - @Jijidici - 27/01/2014
************************************************************************ */

#include "physics/INKPhysicSolid.h"

#include "renderer/shapes/INKCustomShape.h"

INKPhysicSolid::INKPhysicSolid(std::vector<glm::vec3>& vertices)
	: INKRenderable(new INKCustomShape())
	, _vertices() {
	INKCustomShape* pCastCustomShape = static_cast<INKCustomShape*>(_pShape);

	for(unsigned int i=0; i<vertices.size(); ++i) {
		_vertices.push_back(vertices[i]);

		//build geometry
		if(i == 0) {
			pCastCustomShape->addPoint(vertices[0]);
		} else if(i%2 ==1) {
			pCastCustomShape->addPoint(vertices[1 + i/2]);
		} else {
			pCastCustomShape->addPoint(vertices[vertices.size() - i/2]);
		}
	}
	pCastCustomShape->setBuildType(INKCustomShape::eStrip);
	pCastCustomShape->build();
}

INKPhysicSolid::~INKPhysicSolid() {

}