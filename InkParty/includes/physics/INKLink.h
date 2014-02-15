/* ***********************************************************************
	INKLink.h - @Jijidici - 15/02/2014
************************************************************************ */

#ifndef __INK_LINK_H__
#define __INK_LINK_H__

class INKLink {
public:
	INKLink(int iP1Id, int iP2Id, float fLinkLength);
	~INKLink();

	int getP1Id() { return _iP1Id; }
	int getP2Id() { return _iP2Id; }
	float getLength() { return _fLinkLength; }

protected:
	int _iP1Id;
	int _iP2Id;
	float _fLinkLength;
};

#endif //__INK_LINK_H__