#include<iostream>

using namespace std;

double Add(int val1, double val2)
{
	decltype(val1 + val2) sum = val1 + val2;
		return sum;
}

int main()
{
	cout << Add(3, 4.5) << endl;
}