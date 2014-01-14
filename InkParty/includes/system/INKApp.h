/* ***********************************************************************
	INKApp.h - @Jijidici - 09/01/2014
************************************************************************ */

#ifndef __IKP_APP_H__
#define __IKP_APP_H__

#include <vector>
#include "system/INKFrame.h"
#include "renderer/INKRenderable.h"
#include "event/INKEvent.h"
#include "event/INKEventListener.h"

class INKApp : public INKEventListener {
public:
	INKApp();

	void OnExecute	();

	virtual void onEvent(INKEvent* pE);

private:
	void init		();
	void launch		();
	void quit		();

	INKFrame*	_pMainFrame;
	bool		_bLoop;
	std::vector<INKRenderable*> particles;
};

#endif