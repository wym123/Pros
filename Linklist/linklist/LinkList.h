#pragma once

#ifdef _MSC_VER

	#ifdef LIB_EXPORT
		#define LIB __declspec(dllexport)
	#else
		#define LIB __declspec(dllimport)
	#endif // _MSC_VER

#else
	#define LIB
#endif


#include<initializer_list>									//C++ 11֮���еĳ�ʼ���б�[]�����ŵĸ�ֵ��ʽ

template<class T>
class LIB CLinkList
{
private:
	T m_tData;
	CLinkList *m_pNext;										//the point to the next obj
	size_t m_nLen;											//the length of the Linklist	�ӵ�ǰ�ڵ㿪ʼ��ĩβ�ڵ�����ĳ���

public:
	CLinkList(T val);
	CLinkList(std::initializer_list<T> l);       //����C++�Դ��ĳ�ʼ����ʽ������������֧�ֶ����ʱ������̳�ʼ��
	//�������졢��ֵ����Ҫ��������˴���д��
	~CLinkList();

private:
	bool  operator !=(CLinkList<T>& obj);					//�ڲ���ϵ���жϣ����أ�=����

	//bool  operator ==(CLinkList<T>& obj);					//�ڲ���ϵ���жϣ�����==����
	
public:
	void push_back(const T& val);							//β�巨
	void insert(int nIndex, const T& val);					//����
	void insert(CLinkList<T>& pos, const T& val);			//����
	T& operator [](int nIndex);								//�޸�
	CLinkList<T>& GetObj(int nIndex);						//��ȡ����
	void print() const;										//��ӡ
	inline size_t size() const;								//��ǰ����ĳ��Ȼ�ȡ
};

template<class T>
CLinkList<T>::CLinkList(T val)
	:m_tData(val)
	, m_nLen(1)
	, m_pNext(nullptr)
{

}

template<class T>
CLinkList<T>::CLinkList(std::initializer_list<T> l)
{
	auto iter = l.begin();
	m_tData = *iter++;
	m_nLen = 1;
	while (iter < l.end())
		push_back(*iter++);

}
template<class T>
CLinkList<T>::~CLinkList()
{
	delete m_pNext;						//�ݹ��������������������һ��һ���������ȥ
	m_pNext = nullptr;
}

template<class T>
bool  CLinkList<T>::operator !=(CLinkList<T>& obj)				//���أ�=����
{
	if (m_tData != obj.m_tData || m_nLen != obj.m_nLen || m_pNext != obj.m_pNext)
		return true;
	return false;
}

template<class T>
CLinkList<T>& CLinkList<T>::GetObj(int nIndex)
{
	if (nIndex >= m_nLen)
	{
		cout << "Warning : �����±�Խ�� ��";
		return *this;
	}
	size_t i;
	auto p = this;
	for (i = 0; i < nIndex; i++)
		p = p->m_pNext;
	return *p;
}

template<class T>
void CLinkList<T>::push_back(const T& val)//β�巨
{
	auto p = this;
	while (p->m_pNext)
		p = p->m_pNext;
	p->m_pNext = new CLinkList<T>(val);

	size_t nBak = m_nLen + 2;
	auto ptr = this;
	while (ptr != p)
	{
		nBak = ++ptr->m_nLen;
		ptr = ptr->m_pNext;
	}
	ptr->m_nLen = nBak - 1;

}
template<class T>
void CLinkList<T>::insert(int nIndex, const T& val)					//����
{
	auto p = GetObj(nIndex);								//�ҵ���Ҫ�����λ��Index�ڵ�
	if (p != *this)
	{
		size_t nBak;
		auto ptr = this;
		auto pTail = p.m_pNext;										//���м����,����Ͽ�ĩβ������
		p.m_pNext = new CLinkList<T>(val);								//�����ϵĵط����һ���µ�������
		while (ptr != p.m_pNext)										//�˴����ڸ���ǰ��ڵ�ĳ���ֵ
		{
			nBak = ++ptr->m_nLen;
			ptr = ptr->m_pNext;
		}
		ptr->m_nLen = nBak - 1;
		ptr->m_pNext = pTail;											//ǰ��Ľڵ���������
	}
	else
	{
		cout << "���������±�Խ�磡";
		return;
	}


}

template<class T>
void CLinkList<T>::insert(CLinkList<T>& pos, const T& val)
{
	auto p = this;
	while (*p != pos && !p)//����ģ�=����Ҫ�������أ���Ϊ����һ���µ����ͣ����ܼ򵥵Ķ��������=���ţ�Ҫдһд����
		p = p->m_pNext;
	if (!p)
	{
		size_t nBak;
		auto ptr = this;
		auto pTail = p->m_pNext;
		p->m_pNext = new CLinkList<T>(val);
		while (ptr != p->m_pNext)
		{
			nBak = ++ptr->m_nLen;
			ptr = ptr->m_pNext;
		}
		ptr->m_nLen = nBak - 1;
		ptr->m_pNext = pTail;
	}
}

template<class T>
T& CLinkList<T>::operator [](int nIndex)								//�޸�
{
	if (nIndex >= m_nLen)
	{
		cout << "Warning : �����±�Խ�� ��";
		return this->m_tData;
	}
	size_t i;
	auto p = this;
	for (i = 0; i < nIndex; i++)
		p = p->m_pNext;
	return p->m_tData;
}
template<class T>
void CLinkList<T>::print()	const										//��ӡ
{
	auto p = this;
	while (p)
	{
		cout << p->m_tData << " ";
		p = p->m_pNext;
	}
}

template<class T>
size_t CLinkList<T>::size() const
{
	return m_nLen;
}

template class LIB CLinkList<int>;