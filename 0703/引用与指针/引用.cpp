#include<iostream>

struct STest 
{
	double &rfdate;//这里没有初始化引用哦！！！看第38行出现的结果，竟然是4字节（指针呐）！！！
};

int main()
{
	int data = 5,obj = 3;
	int *p = &data, &r = data ;//&r引用：一经定义就需要立刻初始化，初始化为指向的对象
	//002C5EA6  lea         eax, [data]
	//	002C5EA9  mov         dword ptr[p], eax
	//	002C5EAC  lea         eax, [data]
	//	002C5EAF  mov         dword ptr[r], eax
	std::cout << "*p = " << *p <<", data = "<<data<<",obj = "<<obj<<",r = "<<r<<std::endl;// TYPE &r = object;
	p = &obj;
	std::cout << "*p = " << *p <<", data = " << data << ",obj = " << obj << ",r = " << r << std::endl;
	
	r = obj;//引用不改变指向的，引用者与被引用者 “同进退共改变” ，就是直接把盒子里的花生变成了黄豆，而不是改变成装黄豆的盒子
	std::cout << "r=" << r << ", data = " << data << std::endl;

	//指针可以修改指向，而且可以为空
	p = nullptr;//int &ra;//引用必须初始化，指针不必，但是要避免野指针
	//const如果出现在*前面，表示值不可更改而指向可以更改：const int *pa,pa指向的值不可更改
	//const如果出现在*后面，表示数值可以更改，指针指向不可以更改也就是0x000bdf41不可以跟更改
	int * const pa = NULL;//这个就类似引用&的表达方式，int *const pa 等价于 &pa

	double fDate = 3.14;
	double *pfDate = &fDate, &rfDate = fDate;
	std::cout << "sizeof(pfdate) = " << sizeof(pfDate) \
		<< ",sizeof(rfdate) = " << sizeof(rfDate) <<std:: endl;

	std::cout << "sizeof(*pfdate) = " << sizeof(*pfDate) \
		<< ",sizeof(rfdate) = " << sizeof(&rfDate) << std::endl;

	//结构体证明，结构体，类，枚举体，联合体这些可以只声明而不定义内存体
	std::cout << "sizeof(STest) = " << sizeof(STest) << std::endl;
	return EXIT_SUCCESS;
}