#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	//ʱ�����Ϸ�����1������1/2����+1������
	//2��ֻ���˵�ǰһ������ʣ���1/2
	//3������1/2����+1
	//4������1/2+1
	//5��1��
	int num = 1;
	num = (num + 1) * 2;
	num = (num + 1) * 2;
	num = num * 2;
	num = (num + 1) * 2;
	printf("����������%d", num);
	return 0;
}