/* ***********************************************************************
	INKEventManager.cpp - @Jijidici - 09/01/2014
************************************************************************ */
#include "event/INKEventManager.h"

#include "SDL.h"
#include "system/INKFrame.h"
#include "event/INKEventListener.h"
#include "event/INKQuitEvent.h"
#include "event/INKKeyEvent.h"
#include "event/INKMouseDownEvent.h"
#include "event/INKMouseMoveEvent.h"

static INKEventManager* _pInstance = nullptr;

INKEventManager* INKEventManager::getInstance() {
	if(_pInstance == nullptr) {
		_pInstance = new INKEventManager();
	}

	return _pInstance;
}

void INKEventManager::addListener(INKEventListener* pListener, EEventType type) {
	switch(type) {
	case eQuitEvent:
		_quitEventListeners.push_back(pListener);
		break;

	case eKeyEvent:
		_keyEventListeners.push_back(pListener);
		break;

	case eMouseDownEvent:
		_mouseDownEventListeners.push_back(pListener);
		break;

	case eMouseMoveEvent:
		_mouseMoveEventListeners.push_back(pListener);
		break;

	default:
		break;
	}
}

bool INKEventManager::removeListener(INKEventListener* pListener, EEventType type) {
	std::vector<INKEventListener*> vectorToWorkOn;
	switch (type)
	{
	case eQuitEvent:
		vectorToWorkOn = _quitEventListeners;
		break;

	case eKeyEvent:
		vectorToWorkOn = _keyEventListeners;
		break;

	case eMouseDownEvent:
		vectorToWorkOn = _mouseDownEventListeners;
		break;

	case eMouseMoveEvent:
		vectorToWorkOn = _mouseMoveEventListeners;
		break;

	default:
		return false;
		break;
	}

	for(std::vector<INKEventListener*>::iterator it=vectorToWorkOn.begin(); it!=vectorToWorkOn.end(); ++it) {
		if(*it == pListener) {
			vectorToWorkOn.erase(it);
			return true;
		}
	}

	return false;
}

void INKEventManager::manageEvent(INKFrame* pMainFrame) {
	SDL_Event e;
	while(pMainFrame->pollEvent(e)) {
		switch(e.type) {
			case SDL_QUIT:
				sendEvent(new INKQuitEvent(), _quitEventListeners);
				break;

			case SDL_KEYDOWN:
				sendEvent(new INKKeyEvent(e.key.keysym), _keyEventListeners);
				break;

			case SDL_MOUSEBUTTONDOWN:
				sendEvent(new INKMouseDownEvent(glm::vec2(e.button.x, e.button.y), SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1), SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(3)), _mouseDownEventListeners);
				break;

			case SDL_MOUSEMOTION:
				sendEvent(new INKMouseMoveEvent(glm::vec2(e.motion.x, e.motion.y), SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1), SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(3)), _mouseMoveEventListeners);
				break;
		}
	}
}

INKEventManager::INKEventManager() {

}

INKEventManager::~INKEventManager() {
	_quitEventListeners.clear();
	_keyEventListeners.clear();
	_mouseMoveEventListeners.clear();

	_pInstance = nullptr;
}

void INKEventManager::sendEvent(INKEvent* pEvent, std::vector<INKEventListener*> listeners) {
	for(std::vector<INKEventListener*>::iterator it=listeners.begin(); it!=listeners.end(); ++it) {
		(*it)->onEvent(pEvent);
	}

	delete pEvent;
}