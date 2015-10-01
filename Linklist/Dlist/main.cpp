#include <cstdio>
#include "DList.h"

int main()
{
	CDList l = { 1, 2, 3, 4, 5, 6, 7 };
	l.print();
	printf("\n");
	l.erase(l.s_pHead);
	l.print();
	printf("\n");
	l.erase(l.s_pTail);
	l.print();
	printf("\n");
	l.erase(l.s_pHead->m_pNext);
	l.print();
	printf("\n");
	return 0;
}