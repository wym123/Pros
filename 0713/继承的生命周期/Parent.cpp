#include <iostream>
#include "Parent.h"
using namespace std;

CParent::CParent(int x /* = 0 */,int y /* = 0 */)//Ĭ�ϲο�ֵ�����꣨0��0��
	:m_nX(x)
	,m_nY(y)
{

}


CParent::~CParent()
{
}

void CParent::SetPos(int x, int y)
{
	m_nX = x;//
	m_nY = y;
}

void  CParent::ShowPos() const
{
	cout <<"("<< m_nX <<"," <<m_nY <<")"<< endl;
}