#include<iostream>

#define MAX(a,b) ((a) > (b) ? (a) : (b))

using namespace std;
int main()
{
	int a = 4, b = 5;
	cout << MAX(a++, ++b) << endl;
 	return 0;
}