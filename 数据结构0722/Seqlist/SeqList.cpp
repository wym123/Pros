
#include "SeqList.h"
using namespace std;
template <class T, size_t N>
CSeqList<T, N>::CSeqList()
{

}
template <class T, size_t N>
CSeqList(const CSeqList<T, N>& obj);					//��������

template <class T, size_t N>
CSeqList<T, N>& operator =(const CSeqList<T, N>& obj);	//��ֵ����

template <class T, size_t N>
CSeqList::~CSeqList()
{

}

template <class T, size_t N>
bool IsFull() const;

template <class T, size_t N>
bool IsEmpty() const;

// ��
template <class T, size_t N>
void push_front(const T& val);					// ͷ�巨

template <class T, size_t N>
void push_back(const T& val);					// β�巨

template <class T, size_t N>
CSeqList<T, N>& operator +(const T& val);		// β�巨�����������
// ɾ
void erase(size_t index);						// �����±�ɾ��
// ��
T& modify(size_t index, const T& val);			// �����±��޸�
T& operator [](size_t index);					// �±����


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