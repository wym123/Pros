#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include"ChildDate.h"

int main()
{
	struct CChildDate date;
	date.pInit = CInit;
	date.pDestory = CDestory;


	return 0;
}
