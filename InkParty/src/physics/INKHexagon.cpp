/* ***********************************************************************
	INKHexagon.cpp - @Jijidici - 09/02/2014
************************************************************************ */
#define _USE_MATH_DEFINES

#include "physics/INKHexagon.h"

#include <cmath>

INKHexagon::INKHexagon(int iSegmentCount, float fRadius) {
	float fStepAngle = (2.f*M_PI)/static_cast<float>(iSegmentCount);
	for(int i=0; i<iSegmentCount; ++i) {
		float fCurrentAlpha = i*fStepAngle;
		float fNextAlpha = (i+1)*fStepAngle;

		std::vector<glm::vec3> points;
		points.push_back(fRadius*glm::vec3(cos(fCurrentAlpha), sin(fCurrentAlpha), 0.f));
		points.push_back(fRadius*glm::vec3(cos(fNextAlpha), sin(fNextAlpha), 0.f));
		points.push_back((fRadius+1)*glm::vec3(cos(fNextAlpha), sin(fNextAlpha), 0.f));
		points.push_back((fRadius+1)*glm::vec3(cos(fCurrentAlpha), sin(fCurrentAlpha), 0.f));

		_segments.push_back(new INKPhysicSolid(points, 1.f));
	}
}

INKHexagon::~INKHexagon() {
	for(std::vector<INKPhysicSolid*>::iterator itSolid=_segments.begin(); itSolid!=_segments.end(); ++itSolid) {
		delete *itSolid;
		*itSolid = nullptr;
	}
	_segments.clear();
}

void INKHexagon::draw() {
	for(std::vector<INKPhysicSolid*>::iterator itSolid=_segments.begin(); itSolid!=_segments.end(); ++itSolid) {
		(*itSolid)->getShape()->draw();
	}
}

void INKHexagon::computeCollision(glm::vec3 partPos, float fPartMass, glm::vec3 partNextPos, glm::vec3 partNextVel, float fDt, glm::vec3& partForce) {
	for(std::vector<INKPhysicSolid*>::iterator itSolid=_segments.begin(); itSolid!=_segments.end(); ++itSolid) {
		(*itSolid)->computeCollision(partPos, fPartMass, partNextPos, partNextVel, fDt, partForce);
	}
}