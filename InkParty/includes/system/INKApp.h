/* ***********************************************************************
	INKApp.h - @Jijidici - 09/01/2014
************************************************************************ */

#ifndef __IKP_APP_H__
#define __IKP_APP_H__

#include <vector>
#include "system/INKFrame.h"
#include "system/INKCamera.h"
#include "event/INKEvent.h"
#include "event/INKEventListener.h"
#include "physics/INKParticleSystem.h"
#include "physics/INKPhysicSolid.h"

class INKApp : public INKEventListener {
public:
	INKApp();

	void OnExecute	();

	virtual void onEvent(INKEvent* pE);

private:
	void init		();
	void launch		();
	void quit		();

	INKFrame*			_pMainFrame;
	bool				_bLoop;

	INKCamera*			_pCamera;
	INKParticleSystem*	_pPartSystem;
	INKPhysicSolid*		_pRendTest;
};

#endif