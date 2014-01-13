/* ***********************************************************************
	INKEventManager.h - @Jijidici - 09/01/2014
************************************************************************ */

#ifndef __INK_EVENT_MANAGER_H__
#define __INK_EVENT_MANAGER_H__

#include <vector>

#include "event\INKEvent.h"
#include "event/INKEventListener.h"
#include "system/INKFrame.h"

class INKEventManager {
public:
	static INKEventManager* getInstance();

	void					addListener(INKEventListener* pListener, EEventType type);
	bool					removeListener(INKEventListener* pListener, EEventType type);

	void					manageEvent(INKFrame* pMainFrame);

private:

			INKEventManager();
			~INKEventManager();

	void	sendEvent(INKEvent* pEvent, std::vector<INKEventListener*> listeners);

	std::vector<INKEventListener*>	_quitEventListeners;
	std::vector<INKEventListener*>	_keyEventListeners;
};

#endif //__INK_EVENT_MANAGER_H__