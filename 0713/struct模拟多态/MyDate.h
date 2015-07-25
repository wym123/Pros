#pragma once

struct CMyDate
{
	int m_nYear;
	int m_nMonth;
	int m_nDay;
	void (*pInit)( struct CMyDate *p ,int year, int month, int day);//构造函数，第一个参数是模拟this指针
	void(*pDestroy)(struct CMyDate *p);//析构函数
	int(*pJudge)(struct CMyDate *p);//这是个虚函数
};

void PInit(struct CChildDate *p, int year, int month, int day);
void PDestory(struct CMyDate *p);
