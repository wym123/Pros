#pragma once

#ifdef _MSC_VER
		#ifdef LIB_EXPORT
			#define  LIB __declspec(dllexport)
		#else
			#define LIB __declspec(dllimport)
		#endif
#else 
		#define  LIB
#endif // _MSC_VER

#include <istream>
#include <ostream>
#include <sstream>
#include <iostream>

template <class T,size_t N>			//size_t = int
class LIB CSeqList
{
private:
	T m_tData[N];
	size_t m_nSize;
private:
	//�ڲ��ӿ�
	bool IsFull() const;		
	bool IsEmpty() const;

public:
	enum EREL
	{
		REL_EQUAL = 0x01,
		REL_ABOVE = 0x02,
		REL_BELOW = 0x04,
		REL_UNEQUAL = 0x06,
		REL_MORE = 0x03,
		REL_LESS = 0x05,
	};
	//�߼�ö��
	enum ESet
	{
		SET_AND = 0x01, 
		SET_OR = 0x20,
		SET_DEC = 0x40
	};

public:
	CSeqList();
	CSeqList(const CSeqList<T, N>& obj);					//��������
	CSeqList<T, N>& operator =(const CSeqList<T, N>& obj);	//��ֵ����
	~CSeqList();
	// ��
	void push_front(const T& val);					// ͷ�巨
	void push_back(const T& val);					// β�巨
	inline void insert(int index, const T& val);	// ����
	CSeqList<T, N>& operator +(const T& val);		// β�巨�����������
	// ɾ
	void erase(size_t index);						// �����±�ɾ��
	// ��
	T& modify(size_t index, const T& val);			// �����±��޸�
	T& operator [](size_t index);					// �±����
	// ��
	inline size_t size() const;						// ��ѯ����
	size_t find(const T& val);						// ��ֵ����
	// ��ǿ�͹�ϵ���Һ���
	size_t* find_if(ERel rel, const T& val);		// ��ѯ���Ϲ�ϵ����������
	size_t* operator ==(const T& val);				// ��ѯ���������ֵ���±�
	size_t* operator >(const T& val);				// ��ѯ���������ֵ���±�
	size_t* operator <(const T& val);				// ��ѯС�������ֵ���±�
	size_t* operator !=(const T& val);				// ��ѯ�����������ֵ���±�
	size_t* operator >=(const T& val);				// ��ѯ���ڻ���������ֵ���±�
	size_t* operator <=(const T& val);				// ��ѯС�ڻ���������ֵ���±�
	// ��ǿ�͵��߼�������
	size_t* deal(ESet set, size_t* list1, size_t* list2);	// ���ϴ���	
	size_t* and(size_t* list1, size_t* list2);				// ����
	size_t* operator &&(size_t* l);
	size_t* or(size_t* list1, size_t* list2);				// ����
	size_t* operator ||(size_t* l);
	size_t* dec(size_t* list1, size_t* list2);				// �
	size_t* operator -(size_t* l);
	// ��ǿ����ɾ��
	template<class U,size_t N1,size_t N2>
	friend CSeqList<U, N1 + N2> operator +(const CSeqList<U, N1>& obj1, const CSeqList<U, N1>& obj2)
	{

	}
	friend CSeqList<U, N1 + N2> operator -(const CSeqList<U, N1>& obj1, const CSeqList<U, N1>& obj2)
	{

	}
	friend std::istream& operator >>(std::istream& in, CSeqList<T, N>& obj)
	{

	}
	friend std::ostream& operator <<(std::ostream& out, const CSeqList<T, N>& obj)
	{

	}
};
template<class T,size_t N>
size_t CSeqList<T, N>::size() const					// ��ѯ����
{

}