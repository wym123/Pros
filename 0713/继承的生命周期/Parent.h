#pragma once
#include "Macro.h"
//ָ�ľ�����Ϸ�ı���
class CParent
{
private:
	int m_nX;//���ǵ���
	int m_nY;
public:
	CParent(int x = 0,int y = 0);
	~CParent();
	virtual void SetPos(int x, int y);
	void ShowPos() const;
	PROPERTY(int, X, m_nX);//��Ա�������漼���ɣ��ú���д
	PROPERTY(int, Y, m_nY);//
};

