#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_SIZE 10
//10 2 2 ��2ȡ�൹����,�����ȡ˳���ջ˳��һ��
void IntegerDec2Bin(int num, int *pArr, int *pTop)
{
	while (num)
	{
		pArr[(*pTop)++] = num % 2;//ȡ������top���������ģ��������λ��
		num = num / 2;			  //chuyi2
	}
}
void Print(int *pArr,int top)
{
	printf("ת����2����֮���ǣ�");
	while (--top >=0)
	{
		printf("%d", pArr[top]);
	}
}

int main()
{
	int num,top = 0; 
	int arr[MAX_SIZE];
	printf("������һ������ʮ���Ƶģ�\n");
	scanf("%d", &num);
	IntegerDec2Bin(num, arr, &top);
	Print(arr, top);

	return 0;
}//����������Ʋٳ��ܣ��ӵĻ�����˳ʱ���ܣ����Ļ�������ʱ���ܣ�һȦ�ж೤Ҳ���ǻ�״����
//���ȣ������Ƕ��٣���ס���Ｋ�ط�
//
//-128

//128