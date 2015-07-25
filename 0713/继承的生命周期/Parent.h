#pragma once
#include "Macro.h"
//指的就是游戏的背景
class CParent
{
private:
	int m_nX;//这是电流
	int m_nY;
public:
	CParent(int x = 0,int y = 0);
	~CParent();
	virtual void SetPos(int x, int y);
	void ShowPos() const;
	PROPERTY(int, X, m_nX);//成员函数的奇技淫巧，用宏来写
	PROPERTY(int, Y, m_nY);//
};

