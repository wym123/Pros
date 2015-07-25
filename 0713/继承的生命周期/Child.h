#pragma once


#include "Parent.h"

class CChild
	:public CParent
{
private:
	int m_nX;
	int m_nY;
	CParent *m_pParent;
public:
	CChild(CParent *p,int x = 0, int y = 0);
	~CChild();

	void SetParent(CParent *p);

	virtual void SetPos(int x, int y);
	void ShowPos() const;
	PROPERTY(int, X, m_nX);
	PROPERTY(int, Y, m_nY);
};

