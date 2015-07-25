#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "ChildDate.h"

//CChildDate::CChildDate(int year, int month, int day)
//	: CMyDate(year, month, day)
//{
//	// CMyDate::m_nYear 完整写法
//	m_bIsLeapYear = (m_nYear % 4 == 0 && m_nYear % 100 != 0) || (m_nYear % 400 == 0);
//	cout << "Call CChildDate Constructor!\n";
//}
//
//CChildDate::~CChildDate()
//{
//	cout << "Call CChildDate Destructor!\n";
//}

void CInit(struct CChildDate *p, int year, int month, int day)
{
	((struct CMyDate *)p)->pInit = PInit;
	((struct CMydate*)p)->pInit(year, month, day);
	p->pInit = CInit;

	p->m_bIsLeapYear = (p->obj.m_nYear % 4 == 0 && p->obj.m_nYear % 100 != 0) || (p->obj.m_nYear % 400 == 0);
	PInit(p, year, month, day);
	printf("调用子类的构造函数！！！");
}
void CDestory(struct CChildDate* p)
{
	
	printf("调用子类的析构函数！！！");
	PDestory(p);

}
int CJudge(struct CChildDate* p)
{
	p->m_bIsLeapYear = (p->obj.m_nYear % 4 == 0 && p->obj.m_nYear % 100 != 0) || (p->obj.m_nYear % 400 == 0);
	return p->m_bIsLeapYear;
}