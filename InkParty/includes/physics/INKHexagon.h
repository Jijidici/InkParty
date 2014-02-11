/* ***********************************************************************
	INKHexagon.h - @Jijidici - 09/02/2014
************************************************************************ */
#ifndef __INK_HEXAGON_H__
#define __INK_HEXAGON_H__

#include <vector>
#include "physics/INKPhysicSolid.h"

class INKHexagon {
public:
	INKHexagon(int iSegmentCount, float fRadius);
	~INKHexagon();

	void hideSegments(int iHiddenCount);
	void draw();
	void computeCollision(glm::vec3 partPos, float fPartMass, glm::vec3 partNextPos, glm::vec3 partNextVel, float fDt, glm::vec3& partForce);

protected:
	int	  _iSegmentCount;
	float _fRadius;
	std::vector<INKPhysicSolid*> _segments;
	std::vector<bool> _showSeg;
};

#endif //__INK_HEXAGON_H__