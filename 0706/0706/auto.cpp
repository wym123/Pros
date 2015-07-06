#include<iostream>

const int LENGTH = 10;
using namespace std;


	int Add(int a, int b)
	{
		return a + b;
	}

int main()
{
	/*int(A::*pFun)(int, int) = A::Add;*/
	/*int(*pFun)(int, int) = Add;*/

	auto pFun = Add;
	//auto 编译时自动推到,自动识别数组里面的元素，然后负责操作
	cout<<pFun(3, 4)<<endl;
	int arr[LENGTH];
	for (auto element : arr)
	{
		cin >> element;
	}
	for (auto& element : arr)
		cout << element << " ";
	cout<< endl;
	return 0;
}