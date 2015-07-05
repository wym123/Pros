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
extern "C" void Test();//C++的编译环境里可以用，给编译器看的，如果遇到extern “C”后面按照C语言的方式编译

int main()
{/*
	int a = 1, b = 2 , c;
	c = ADD(a, b);
	printf("c = %d", c);
	return 0;*/
	print();//重载就是根据你的输入参数来选择的寻找同名的函数
	print(" iloveyou");
	print("wym", 3);
	return 0;

}