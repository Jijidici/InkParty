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
					INKCustomShape();
	virtual			~INKCustomShape();

	virtual void	build();
	void			addPoint(glm::vec3 point) { _points.push_back(point); }

protected:
	std::vector<glm::vec3>	_points; 
};

#endif //__INK_CUSTOM_SHAPE_H__