/* ***********************************************************************
	INKEvent.h - @Jijidici - 09/01/2014
************************************************************************ */

#ifndef __INK_EVENT_H__
#define __INK_EVENT_H__


enum EEventType {
	eQuitEvent,
	eKeyEvent,
	eMouseMoveEvent
};

class INKEvent {
public :
	INKEvent(EEventType type) : _type(type) {}

	inline EEventType getType() { return _type; }

private:
	EEventType _type;
};

#endif //__INK_EVENT_H__