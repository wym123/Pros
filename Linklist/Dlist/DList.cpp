#include <cstdio>
#include "DList.h"
using namespace std;

CDList* CDList::s_pHead = nullptr;			//�ȼ���ͷβ���ǿյ�
CDList* CDList::s_pTail = nullptr;
CDList::CDList(int val)
	:m_nData(val)
	, m_pFront(nullptr)
	, m_pNext(nullptr)
{
	if (!s_pHead)
		s_pHead = this;						//��ͷβ���г�ʼ��
	if (!s_pTail)
		s_pTail = this;
}

CDList::CDList(std::initializer_list < int > l)
{
	auto iter = l.begin();
	m_nData = *iter++;
	m_pNext = nullptr;
	m_pFront = nullptr;
	if (!s_pHead)
		s_pHead = this;						//�����أ�����ģ���ʼ��һ����
	if (!s_pTail)
		s_pTail = this;
	while (iter < l.end())
	{
		push_back(*iter++);
	}
}

CDList::~CDList()
{
	if (this == s_pHead)
		s_pHead = m_pNext;
	if (this == s_pTail)
		s_pTail = m_pFront;
}
void CDList::push_front(int val)
{
	CDList *p = new CDList(val);
	s_pHead->m_pFront = p;
	p->m_pNext = s_pHead;
	s_pHead = p;
}
void CDList::push_back(int val)
{
	CDList *p = new CDList(val);
	p->m_pFront = s_pTail;
	s_pTail->m_pNext = p;
	s_pTail = p;
}
void CDList::erase(const CDList* pos)
{
	auto head = pos->m_pFront, tail = pos->m_pNext;
	if (pos == s_pHead)
	{
		if (pos != this)
			delete pos;
		s_pHead = tail;
		s_pHead->m_pFront = nullptr;
	}
	else if (pos == s_pTail)
	{
		if (pos != this)
			delete pos;
		s_pTail = head;
		s_pTail->m_pNext = nullptr;
	}
	else{
		delete pos;
		head->m_pNext = tail;
		tail->m_pFront = head;
	}
}
void CDList::print() const//��Ա��������const����������������������������ݳ�Ա��׼ȷ��˵�ǷǾ�̬���ݳ�Ա�����κθı䡣 
{
	CDList* p = s_pHead;
	while (p != s_pTail->m_pNext)
	{
		printf("%d ", p->m_nData);
		p = p->m_pNext;
	}
}