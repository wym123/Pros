#include <iostream>
using namespace std;
int main()
{
	int a = 3,b = 7;
	int *pa = &a;
	int * &rpa = pa;		//����ط�����д��һ��ָ������ã�rpa��pa����ĵ�ֵַ��ȡ�����˸���rpa����
							//����*rpa=a=3
	int ** const ppA = &pa; //pa�����ŵľ���һ����ַ��**ppA����ָ�������ַ�ģ�Ҳ����ָ��ָ���ָ��
	*rpa = 5;				//rpa�͵ȼ���*ppA
	cout << "a = "<<a<<" *pa="<<*pa<<" *rpa ="<<*rpa<< endl;
	cout << "&a = " << static_cast<void*>(&a) << ", &b" << static_cast<void*>(&b) << endl;
	cout << "��ַ rpa" << static_cast<void*>(rpa) << ",��ַ pa" << static_cast<void*>(pa) << endl;
	pa = &b;
	cout << "a = " << a << " *pa=" << *pa << " *rpa =" << *rpa << endl;
	cout << "&a = " << static_cast<void*>(&a) << ", &b" << static_cast<void*>(&b) << endl;
	cout << "��ַ rpa" << static_cast<void*>(rpa) << ",��ַ pa" << static_cast<void*>(pa) << endl;

	return 0;
}
