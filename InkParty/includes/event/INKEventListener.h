/* ***********************************************************************
	INKEventManager.h - @Jijidici - 09/01/2014
************************************************************************ */

#ifndef __INK_EVENT_LISTENER_H__
#define __INK_EVENT_LISTENER_H__

#include "event/INKEvent.h"

class INKEventListener {
public:
	~INKEventListener() {}

	virtual void onEvent(INKEvent* pE) = 0;
};

#endif