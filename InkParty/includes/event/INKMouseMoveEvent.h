/* ***********************************************************************
	INKMouseMoveEvent.h - @Jijidici - 09/01/2014
************************************************************************ */

#ifndef __INK_MOUSE_EVENT_H__
#define __INK_MOUSE_EVENT_H__

#include <glm.hpp>
#include "event/INKEvent.h"

class INKMouseMoveEvent : public INKEvent {
public:
	INKMouseMoveEvent(glm::vec2 mousePos, bool bLeft, bool bRight);

	glm::vec2 getMousePos() { return _mousePos; }
	bool isLeftButtonPressed() { return _bLeftPressed; }
	bool isRightButtonPressed() { return _bRightPressed; }

protected:
	glm::vec2 _mousePos;
	bool _bLeftPressed;
	bool _bRightPressed;
};

#endif //__INK_MOUSE_EVENT_H__