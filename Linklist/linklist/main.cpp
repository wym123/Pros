#include <iostream>
#include "LinkList.h"

using namespace std;

int main()
{
	auto i = 0, j = 0;
	CLinkList<int> l1 = { 2, 3, 4, 5, 6 };
	CLinkList<int> l2 = { 2, 5, 2, 6, 8 };
	CLinkList<int> l3(0);

	auto len1 = l1.size(), len2 = l2.size();
	while (i < len1 && j < len2)
	{
		if (l1[i] < l2[j])
			l3.push_back(l1[i++]);
		else
			l3.push_back(l2[j++]);
	}
	while (i < len1 || j < len2)
	{
		if (i < len1)
			l3.push_back(l1[i++]);
		else
			l3.push_back(l2[j++]);
	}
	l3.print();
	return EXIT_SUCCESS;
}