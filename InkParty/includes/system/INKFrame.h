/* ***********************************************************************
	INKFrame.h - @Jijidici - 09/01/2014
************************************************************************ */

#ifndef __INK_FRAME_H__
#define __INK_FRAME_H__

#include <string>
#include "SDL.h"

class INKFrame {
public:
				INKFrame			(std::string strTitle, int iW, int iH, int iBbp);

	void		init				(int iFps);
	void		quit				();

	bool		pollEvent			(SDL_Event& e) const;

	inline void saveFrameStartTime	() { _iFrameStartTime = SDL_GetTicks(); }
	inline void	setFPS				(int iFps) { _iFps = iFps; _iFrameDuration = 1000 / iFps; }
	float		computeFrameTime	();
	float		getRatio			() { return static_cast<float>(_iH)/static_cast<float>(_iW); }

protected:
	std::string _strTitle;
	int			_iW;
	int			_iH;
	int			_iBbp;

	int			_iFps;

private:
	int			_iFrameDuration;
	int			_iFrameStartTime;
};

#endif // __INK_FRAME_H__