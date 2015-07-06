#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_SIZE 10
//10 2 2 除2取余倒读数,这个读取顺序和栈顺序一致
void IntegerDec2Bin(int num, int *pArr, int *pTop)
{
	while (num)
	{
		pArr[(*pTop)++] = num % 2;//取余数，top用来计数的，计算你的位数
		num = num / 2;			  //chuyi2
	}
}
void Print(int *pArr,int top)
{
	printf("转化成2进制之后是：");
	while (--top >=0)
	{
		printf("%d", pArr[top]);
	}
}

int main()
{
	int num,top = 0; 
	int arr[MAX_SIZE];
	printf("请输入一个数字十进制的：\n");
	scanf("%d", &num);
	IntegerDec2Bin(num, arr, &top);
	Print(arr, top);

	return 0;
}//溢出：联想绕操场跑，加的话按照顺时针跑，减的话按照逆时针跑，一圈有多长也就是环状数轴
//长度，周期是多少，记住，物极必反
//
//-128

//128