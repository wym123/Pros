#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "MyDate.h"

void PInit(struct CMyDate *p, int year, int month, int day)//���캯��
{
	p->m_nYear = year;
	p->m_nMonth = month;
	p->m_nDay = day;
	printf("�����˹��캯����");
}
void PDestory(struct CMyDate *p)//��������
{
	printf("��������������");
}