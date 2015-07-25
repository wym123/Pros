#pragma once

#include "MyDate.h"

struct CChildDate 
{
	struct CMyDate obj;
	int m_bIsLeapYear;
	int(*pvptr)(struct CMyDate*);	//Ðéº¯Êý±í
	void(*pInit)(struct CChildDate *p,int year,int month,int day);
	void(*pDestory)(struct CChildDate *p);
	int(*pJudge)(struct CChildDate* p);
};

void CInit(struct CChildDate *p, int year, int month, int day);
void CDestory(struct CChildDate *p);
int CJudge(struct CChildDate* p);

