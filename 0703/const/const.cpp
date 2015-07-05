#include <iostream>

int main()
{
	const int i = 5;
	int *p =const_cast<int*>( &i);
	*p = 4;
	printf("%d", i);
}