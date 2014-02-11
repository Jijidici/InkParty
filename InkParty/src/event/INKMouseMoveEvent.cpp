/* ***********************************************************************
	INKMouseMoveEvent.cpp - @Jijidici - 09/01/2014
************************************************************************ */

#include "event/INKMouseMoveEvent.h"

INKMouseMoveEvent::INKMouseMoveEvent(glm::vec2 mousePos, bool bLeft, bool bRight)
	: INKEvent(eMouseMoveEvent)
	, _mousePos(mousePos)
	, _bLeftPressed(bLeft)
	, _bRightPressed(bRight) {

}