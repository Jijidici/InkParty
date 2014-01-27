/* ***********************************************************************
	INKCustomShape.h - @Jijidici - 27/01/2014
************************************************************************ */

#ifndef __INK_CUSTOM_SHAPE_H__
#define __INK_CUSTOM_SHAPE_H__

#include <vector>
#include "glm.hpp"
#include "renderer/shapes/INKShape.h"

class INKCustomShape : public INKShape {
public:
	enum EBuildType {
		eFan,
		eStrip
	};
					INKCustomShape();
	virtual			~INKCustomShape();

	virtual void	build();
	virtual void	draw();
	void			addPoint(glm::vec3 point) { _points.push_back(point); }

	void			setBuildType(EBuildType type) { _buildType = type; }

protected:
	std::vector<glm::vec3>	_points; 
	EBuildType				_buildType;
};

#endif //__INK_CUSTOM_SHAPE_H__