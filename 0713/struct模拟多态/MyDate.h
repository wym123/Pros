#pragma once

struct CMyDate
{
	int m_nYear;
	int m_nMonth;
	int m_nDay;
	void (*pInit)( struct CMyDate *p ,int year, int month, int day);//���캯������һ��������ģ��thisָ��
	void(*pDestroy)(struct CMyDate *p);//��������
	int(*pJudge)(struct CMyDate *p);//���Ǹ��麯��
};

void PInit(struct CChildDate *p, int year, int month, int day);
void PDestory(struct CMyDate *p);
