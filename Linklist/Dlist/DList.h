#pragma once

#include <initializer_list>
class CDList
{
public:
	int m_nData;
	CDList *m_pFront;
	CDList *m_pNext;
	static 	CDList *s_pHead;
	static 	CDList *s_pTail;
public:
	CDList(int val);
	CDList(std::initializer_list < int > l);
	void push_front(int val);
	void push_back(int val);
	void erase(const CDList* pos);
	void print() const;
	~CDList();
};

