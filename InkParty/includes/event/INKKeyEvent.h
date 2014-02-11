/* ***********************************************************************
	INKKeyEvent.h - @Jijidici - 09/01/2014
************************************************************************ */

#ifndef __INK_KEY_EVENT_H__
#define __INK_KEY_EVENT_H__

#include "SDL.h"
#include "event/INKEvent.h"

class INKKeyEvent : public INKEvent{
public:
	INKKeyEvent(SDL_keysym key) : INKEvent(eKeyEvent), _key(key) {} 

	inline SDL_keysym getKey() { return _key; }
private:
	SDL_keysym _key;
};

#endif //__INK_KEY_EVENT_H__