#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_SIZE 100

void FractionDec2Bin(double num, int *pArr, int *pTail)
{
	while (num < -1e-6 || num >1e-6)
	{
		pArr[*pTail] = (int)(num * 2);
		num = (num*2) - pArr[(*pTail)++]; 
	}
}

void Print(int *pArr, int head,int tail)
{
	printf("ת����2����֮���ǣ� ");
	printf("0.");
	while (head < tail)
	{
		printf("%d", pArr[head++]);
	}
	printf("\n");
}

int main()
{
	double num;
	int queue[MAX_SIZE], head = 0, tail = 0;
	printf("��������ת�������֣�");

	scanf("%lf", &num);

	FractionDec2Bin(num, queue, &tail);

	Print(queue,head,tail);
	return 0;
}