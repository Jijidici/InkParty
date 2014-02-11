/* ***********************************************************************
	INKHexagon.cpp - @Jijidici - 09/02/2014
************************************************************************ */
#define _USE_MATH_DEFINES

#include "physics/INKHexagon.h"

#include <cstdlib>
#include <ctime>
#include <cmath>

INKHexagon::INKHexagon(int iSegmentCount, float fRadius) 
	: _iSegmentCount(iSegmentCount)
	, _fRadius(fRadius) {
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
		_showSeg.push_back(true);
	}
}

INKHexagon::~INKHexagon() {
	for(std::vector<INKPhysicSolid*>::iterator itSolid=_segments.begin(); itSolid!=_segments.end(); ++itSolid) {
		delete *itSolid;
		*itSolid = nullptr;
	}
	_segments.clear();
}

void INKHexagon::hideSegments(int iHiddenCount) {
	srand(time(nullptr));

	while(iHiddenCount > 0) {
		int iRandomId = rand()%_iSegmentCount;
		if(_showSeg[iRandomId] == true) {
			_showSeg[iRandomId] = false;
			--iHiddenCount;
		}
	}
}

void INKHexagon::draw() {
	for(unsigned int i=0; i<_segments.size(); ++i) {
		if(_showSeg[i] == true) {
			_segments[i]->getShape()->draw();
		}
	}
}

void INKHexagon::computeCollision(glm::vec3 partPos, float fPartMass, glm::vec3 partNextPos, glm::vec3 partNextVel, float fDt, glm::vec3& partForce) {
	float fFromCenterDist = glm::length(partNextPos);

	if(fFromCenterDist >= _fRadius && fFromCenterDist <= _fRadius+1) {
		for(unsigned int i=0; i<_segments.size(); ++i) {
			if(_showSeg[i] == true) {
				_segments[i]->computeCollision(partPos, fPartMass, partNextPos, partNextVel, fDt, partForce);
			}
		}
	}
}