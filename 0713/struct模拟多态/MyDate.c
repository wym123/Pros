#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "MyDate.h"

void PInit(struct CMyDate *p, int year, int month, int day)//构造函数
{
	p->m_nYear = year;
	p->m_nMonth = month;
	p->m_nDay = day;
	printf("调用了构造函数！");
}
void PDestory(struct CMyDate *p)//析构函数
{
	printf("调用析构函数！");
}