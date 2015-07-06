#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_SIZE 10

typedef struct SStack
{
	int arr[MAX_SIZE];
	int top;
}SStack;

typedef struct SQueue
{
	int arr[MAX_SIZE];
	int head;
	int tail;
}SQueue;


void IntergerDec2Bin(int num,SStack *s)
{
	s->top = 0;
	if (!num)
	{
		s->arr[s->top++] = 0;
		return;
	}
	
	while (num)
	{
		s->arr[s->top++] = num % 2;
		num = num / 2;
	}
}

void FractionDec2Bin(double num,SQueue *q)
{
	q->head = q->tail = 0;
	while (num < -1e-6 || num >1e-6)
	{
		q->arr[q->tail] = (int)(num * 2);
		num = num * 2 - q->arr[q->tail++];
	}
}

void Print(SStack *s,SQueue *q)
{
	while (--s->top >= 0)
	{
		printf("%d", s->arr[s->top]);
	}
	printf(".");
	while (q->head < q->tail)
		printf("%d",q->arr[q->head++]);
}

int main()
{
	double num;
	SStack s;
	SQueue q;
	scanf("%lf", &num);
	IntergerDec2Bin((int)num, &s);
	FractionDec2Bin(num - (int)num, &q);
	Print(&s, &q);
	return 0;
}