#include <iostream>
#include "Seqlist.h"

using namespace std;

int main()
{
	CSeqList<int, 10> arr;
	cin >> arr;
	cout << arr << endl;
	auto l1 = arr < 60;
	auto l2 = arr > 90;
	auto l3 = arr.or(l1, l2);
	arr.Print(l3);
	delete[] l1;
	delete[] l2;
	delete[] l3;
	return EXIT_SUCCESS;

}