#include<iostream>

struct STest 
{
	double &rfdate;//����û�г�ʼ������Ŷ����������38�г��ֵĽ������Ȼ��4�ֽڣ�ָ���ţ�������
};

int main()
{
	int data = 5,obj = 3;
	int *p = &data, &r = data ;//&r���ã�һ���������Ҫ���̳�ʼ������ʼ��Ϊָ��Ķ���
	//002C5EA6  lea         eax, [data]
	//	002C5EA9  mov         dword ptr[p], eax
	//	002C5EAC  lea         eax, [data]
	//	002C5EAF  mov         dword ptr[r], eax
	std::cout << "*p = " << *p <<", data = "<<data<<",obj = "<<obj<<",r = "<<r<<std::endl;// TYPE &r = object;
	p = &obj;
	std::cout << "*p = " << *p <<", data = " << data << ",obj = " << obj << ",r = " << r << std::endl;
	
	r = obj;//���ò��ı�ָ��ģ��������뱻������ ��ͬ���˹��ı䡱 ������ֱ�ӰѺ�����Ļ�������˻ƶ��������Ǹı��װ�ƶ��ĺ���
	std::cout << "r=" << r << ", data = " << data << std::endl;

	//ָ������޸�ָ�򣬶��ҿ���Ϊ��
	p = nullptr;//int &ra;//���ñ����ʼ����ָ�벻�أ�����Ҫ����Ұָ��
	//const���������*ǰ�棬��ʾֵ���ɸ��Ķ�ָ����Ը��ģ�const int *pa,paָ���ֵ���ɸ���
	//const���������*���棬��ʾ��ֵ���Ը��ģ�ָ��ָ�򲻿��Ը���Ҳ����0x000bdf41�����Ը�����
	int * const pa = NULL;//�������������&�ı�﷽ʽ��int *const pa �ȼ��� &pa

	double fDate = 3.14;
	double *pfDate = &fDate, &rfDate = fDate;
	std::cout << "sizeof(pfdate) = " << sizeof(pfDate) \
		<< ",sizeof(rfdate) = " << sizeof(rfDate) <<std:: endl;

	std::cout << "sizeof(*pfdate) = " << sizeof(*pfDate) \
		<< ",sizeof(rfdate) = " << sizeof(&rfDate) << std::endl;

	//�ṹ��֤�����ṹ�壬�࣬ö���壬��������Щ����ֻ�������������ڴ���
	std::cout << "sizeof(STest) = " << sizeof(STest) << std::endl;
	return EXIT_SUCCESS;
}