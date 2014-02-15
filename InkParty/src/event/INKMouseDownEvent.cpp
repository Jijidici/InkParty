/* ***********************************************************************
	INKMouseDownEvent.cpp - @Jijidici - 15/02/2014
************************************************************************ */

#include "event/INKMouseDownEvent.h"

INKMouseDownEvent::INKMouseDownEvent(glm::vec2 mousePos, bool bLeft, bool bRight)
	: INKEvent(eMouseDownEvent)
	, _mousePos(mousePos)
	, _bLeftPressed(bLeft)
	, _bRightPressed(bRight) {

}