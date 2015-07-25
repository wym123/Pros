#include <iostream>
#include "Child.h"

using namespace std;


CChild::CChild(CParent *p,int x /* = 0 */, int y /* = 0 */)
	:m_pParent(p)
	, m_nX(x)
	, m_nY(y)
{
	//这是成员函数调用的完整形式
	//m_nX = m_pParent->GetX() + x;//在父类的基础上，+ x
	//m_nY = m_pParent->GetY() + y;//在父类的基础上，+ y
}


CChild::~CChild()
{

}

void CChild::SetPos(int x, int y)
{
	m_nX =  x;
	m_nY =  y;
}
void CChild::ShowPos() const
{
	cout << "(" << m_pParent->GetX() + m_nX << "," <<m_pParent->GetY() + m_nY << ")\n";
	//在绘制的时候实现坐标转换
}

void CChild::SetParent(CParent *p)
{
	m_pParent = p;
}
