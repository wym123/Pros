#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE 20
#include <stdio.h>

typedef struct tagSeqLinkList
{
	int data;
	int next;
}SeqListList;

int main()
{
	int i,j,n,index,head,tail;
	SeqListList l[MAX_SIZE];
	for (i = 0; i < MAX_SIZE; i++)
	{	
		scanf("%d", &l[i].data);
		l[i].next = i + 1;
	}
	l[MAX_SIZE - 1].next = -1;

	printf("������Ҫɾ���������±������");
	scanf("%d", &n);
	printf("������Ҫɾ������������±꣺\n");
	for (i = 0; i < n; i++)
	{
		printf("������Ҫɾ��������");
		scanf("%d", &index);
		j = 0;
		while (l[j].next != -1)
		{
			if (l[j].next == index)
			{
				head = j;
				break;
			}
			j = l[j].next;
		}
		tail = l[index].next;
		l[j].next = tail;
	}

	i = 0;
	while (l[i].next != -1)
	{
		printf("%d ", l[i].data);
		i = l[i].next;
	}

	printf("%d", l[i].data);
	return 0;
}