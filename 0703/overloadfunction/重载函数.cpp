#include <iostream>
#include<string>
#define ADD(a,b)\
	a + b
using namespace std;
void print()
{
	cout << "hello world !" << endl;
}

void print(string s)
{
	cout << s << endl;
}
void print(string s,int n)
{
	int i;
	for (i = 0; i < n;i++)
	{
		cout << s << endl;
	}
}
extern "C" void Test();//C++�ı��뻷��������ã������������ģ��������extern ��C�����水��C���Եķ�ʽ����

int main()
{/*
	int a = 1, b = 2 , c;
	c = ADD(a, b);
	printf("c = %d", c);
	return 0;*/
	print();//���ؾ��Ǹ���������������ѡ���Ѱ��ͬ���ĺ���
	print(" iloveyou");
	print("wym", 3);
	return 0;

}