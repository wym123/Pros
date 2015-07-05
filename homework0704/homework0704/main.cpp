#include <iostream>
using namespace std;
int main()
{
	int a = 3,b = 7;
	int *pa = &a;
	int * &rpa = pa;		//这个地方就是写了一个指针的引用，rpa把pa里面的地址值给取出来了给了rpa，、
							//所以*rpa=a=3
	int ** const ppA = &pa; //pa本身存放的就是一个地址，**ppA就是指向这个地址的，也就是指向指针的指针
	*rpa = 5;				//rpa就等价于*ppA
	cout << "a = "<<a<<" *pa="<<*pa<<" *rpa ="<<*rpa<< endl;
	cout << "&a = " << static_cast<void*>(&a) << ", &b" << static_cast<void*>(&b) << endl;
	cout << "地址 rpa" << static_cast<void*>(rpa) << ",地址 pa" << static_cast<void*>(pa) << endl;
	pa = &b;
	cout << "a = " << a << " *pa=" << *pa << " *rpa =" << *rpa << endl;
	cout << "&a = " << static_cast<void*>(&a) << ", &b" << static_cast<void*>(&b) << endl;
	cout << "地址 rpa" << static_cast<void*>(rpa) << ",地址 pa" << static_cast<void*>(pa) << endl;

	return 0;
}
