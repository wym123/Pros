#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	//时间线上分析：1：吃了1/2总数+1的桃子
	//2：只吃了当前一堆桃子剩余的1/2
	//3：吃了1/2桃子+1
	//4：吃了1/2+1
	//5：1个
	int num = 1;
	num = (num + 1) * 2;
	num = (num + 1) * 2;
	num = num * 2;
	num = (num + 1) * 2;
	printf("桃子总数是%d", num);
	return 0;
}