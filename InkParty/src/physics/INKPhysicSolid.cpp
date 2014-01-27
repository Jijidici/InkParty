/* ***********************************************************************
	INKPhysicSolid.cpp - @Jijidici - 27/01/2014
************************************************************************ */

#include "physics/INKPhysicSolid.h"

#include "renderer/shapes/INKCustomShape.h"

INKPhysicSolid::INKPhysicSolid(std::vector<glm::vec3>& vertices, float elasticity)
	: INKRenderable(new INKCustomShape())
	, _vertices(vertices)
	, _fElasticity(elasticity) {
	INKCustomShape* pCastCustomShape = static_cast<INKCustomShape*>(_pShape);

	for(unsigned int i=0; i<vertices.size(); ++i) {

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

void INKPhysicSolid::computeCollision(INKParticle* pParticle, glm::vec3 partNextPos, glm::vec3 partNextVel, float fDt) {
	for(unsigned int i=0; i<_vertices.size(); ++i) {

			glm::vec2 vtxA = glm::vec2(_vertices[i].x, _vertices[i].y);

			glm::vec2 vtxB;
			if(i+1 == _vertices.size()) {
				vtxB = glm::vec2(_vertices[0].x, _vertices[0].y);
			} else {
				vtxB = glm::vec2(_vertices[i+1].x, _vertices[i+1].y);
			}

			glm::vec2 vecNormale(0.f);
			glm::vec2 vecIntersection(0.f);
			glm::vec2 currentPos = glm::vec2(pParticle->getPosition().x, pParticle->getPosition().y);
			glm::vec2 nextPos = glm::vec2(partNextPos.x, partNextPos.y);
			glm::vec2 nextVel = glm::vec2(partNextVel.x, partNextVel.y);

			if(segmentIntersect(vtxA, vtxB, currentPos, nextPos, vecIntersection, vecNormale)) {
				glm::vec2 forceToAdd = (_fElasticity*glm::dot(nextVel, -vecNormale)*pParticle->getMass()/fDt) * vecNormale;
				pParticle->addForce(glm::vec3(forceToAdd, 0.f));
			}
		}
}

bool INKPhysicSolid::segmentIntersect(glm::vec2 A, glm::vec2 B, glm::vec2 p1, glm::vec2 p2, glm::vec2& intersection, glm::vec2& normale) {
	float fEpsilon = 0.001f; // Permet de tricher en allongeant la taille des coté

    glm::vec2 dir = p2 - p1; // Vecteur p1p2
    glm::vec2 AB = B - A; // Vecteur AB
    glm::vec2 N = glm::vec2(-AB.y, AB.x); // Vecteur normal non unitaire

    // Si le vecteur p1p2 et le vecteur N on la meme direction, il n'y a pas d'intersection
    if(glm::dot(dir, N) >= 0) {
        return false;
    }

    // Calcul du parametre t tel que I = p1 + t x p1p2
    float t = -glm::dot(N, p1 - A) / glm::dot(N, dir);

    // Si t n'est pas dans [0,1], le point d'intersection n'est pas dans le segment [p1,p2]
    if(t < 0.f || t > 1.f) {
        return false;
    }

    glm::vec2 I = p1 + t * dir; // Point d'intersection

    float dot = glm::dot(I - A, AB); // Produit scalaire entre le vecteur AI et le vecteur AB
    if(dot < -fEpsilon || dot > glm::dot(AB, AB) + fEpsilon) {
        return false;
    }

    intersection = I;
	normale = glm::normalize(N);

    return true;
}