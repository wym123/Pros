#include <iostream>
#include "Child.h"

using namespace std;


CChild::CChild(CParent *p,int x /* = 0 */, int y /* = 0 */)
	:m_pParent(p)
	, m_nX(x)
	, m_nY(y)
{
	//���ǳ�Ա�������õ�������ʽ
	//m_nX = m_pParent->GetX() + x;//�ڸ���Ļ����ϣ�+ x
	//m_nY = m_pParent->GetY() + y;//�ڸ���Ļ����ϣ�+ y
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
	//�ڻ��Ƶ�ʱ��ʵ������ת��
}

void CChild::SetParent(CParent *p)
{
	m_pParent = p;
}
