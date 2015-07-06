#include <iostream>
#include <algorithm>//sort()函数所在的头文件内
using namespace std;

const int LENGTH = 10;

int Compare(int num1, int num2)
{
	return num1 < num2;
}
int  main()
{
	int arr[LENGTH];
	for (auto& element:arr)
	{
		cin >> element;
	}
	//sort(arr, arr + LENGTH,Compare);
	sort(arr, arr + LENGTH, [](int a ,int b)->bool{return a < b; });//lambda的

	for (auto& element:arr)
	{
		cout << element << " ";
	}
	cout << endl;
	return 0;
}