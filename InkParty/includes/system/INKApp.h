#ifndef __IKP_APP_H__
#define __IKP_APP_H__

#include "system/INKFrame.h"

class INKApp {
public:
	INKApp();

	void OnExecute	();

private:
	void init		();
	void launch		();
	void quit		();

	INKFrame* _pMainFrame;
};

#endif