#include <iostream>
using namespace std;

int Add(int a, int b)
{
	return a + b;

}

int main()
{
	//lambda��ʽ��
	//[capture](param)modifier->return type{body}
	//<����ֵ>����������������б� ���η� {������}

	[]()//������������
	{
		cout << "hello world!\n";
	}();//()�������������

	auto p1 = []()->void
	{
		cout << "hello world!\n";
	
	};
	p1();

	auto p2 = [](int a, int b)->int{return a + b; };
	cout << p2(3, 4) << endl;

	return 0;
}