#include <iostream>
using namespace std;

int Add(int a, int b)
{
	return a + b;

}

int main()
{
	//lambda形式：
	//[capture](param)modifier->return type{body}
	//<返回值>函数名（传入参数列表） 修饰符 {函数体}

	[]()//这是匿名函数
	{
		cout << "hello world!\n";
	}();//()函数调用运算符

	auto p1 = []()->void
	{
		cout << "hello world!\n";
	
	};
	p1();

	auto p2 = [](int a, int b)->int{return a + b; };
	cout << p2(3, 4) << endl;

	return 0;
}