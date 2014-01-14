/* ***********************************************************************
	INKRenderer.h - @Jijidici - 14/01/2014
************************************************************************ */

#ifndef __INK_RENDERER_H__
#define __INK_RENDERER_H__

class INKRenderer {
public:
	static INKRenderer* getInstance();

	void	init();
	void	render();

private:
	INKRenderer();
	~INKRenderer();
};

#endif //__INK_RENDERER_H__