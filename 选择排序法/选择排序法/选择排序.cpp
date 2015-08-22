#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#define MAXSIZE 10

void Init(int *data,int num)
{
	printf("please enter 10 number :\n");
	for (int i = 0; i < num; i++)
	{
		scanf("%d", &data[i]);
	}
	printf("\n");
}

void Sort(int *data, int num)
{
	int i, j, tmp,min;
	for (i = 0; i < num - 1; i++)
	{
		tmp = i;
		for (j = i + 1; j < num; j++)
		{
			if (data[tmp] > data[j])
				tmp = j;
		}
		if (tmp != i)
		{
			min = data[tmp];
			data[tmp] = data[i];
			data[i] = min;
		}
	}
}

void print(int *data, int num)
{
	for (int i = 0; i < num; i++)
	{
		printf("%d ", data[i]);
	}
}

int main()
{
	int data[MAXSIZE];
	Init(data, MAXSIZE);
	Sort(data, MAXSIZE);
	print(data, MAXSIZE);

	return 0;
}