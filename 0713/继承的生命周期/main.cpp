#include <iostream>
#include "Child.h"

using namespace std;

int main()
{
	CParent bg1(320, 480),bg2(160,200);
	CChild layer(&bg1,20,30);

	bg1.ShowPos();
	cout << endl;
	bg2.ShowPos();
	cout << endl;
	layer.ShowPos();
	cout << endl;
	layer.SetParent(&bg2);
	layer.ShowPos();

	return EXIT_SUCCESS;
}