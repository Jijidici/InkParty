/* ***********************************************************************
	INKQuitEvent.h - @Jijidici - 09/01/2014
************************************************************************ */

#ifndef __INK_QUIT_EVENT_H__
#define __INK_QUIT_EVENT_H__

#include "event/INKEvent.h"

class INKQuitEvent : public INKEvent {
public:
	INKQuitEvent() : INKEvent(eQuitEvent) {}
};

#endif //__INK_QUIT_EVENT_H__