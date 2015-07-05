#include <iostream>
#include <string>
using namespace std;

//void print()
//{
//	cout << "Hello World !" << endl;
//
//}
void print(string s = "wym")//对于有默认参数的函数而言，尽量提供一个参数最多的函数，统一接口
{
	cout << s << endl;
}

int main()
{
	print("i love you");//含有默认参数的函数，尽量不要重载，二义性

	return 0;
}