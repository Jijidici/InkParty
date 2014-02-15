/* ***********************************************************************
	INKApp.h - @Jijidici - 09/01/2014
************************************************************************ */

#ifndef __IKP_APP_H__
#define __IKP_APP_H__

#include <vector>
#include "system/INKFrame.h"
#include "system/INKCamera.h"
#include "renderer/INKGLProgram.h"
#include "event/INKEvent.h"
#include "event/INKEventListener.h"
#include "physics/INKGooParticleSystem.h"

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

	INKGLProgram*		_pParticleProgram;
	INKCamera*			_pCamera;
	INKGooParticleSystem*	_pPartSystem;
};

#endif