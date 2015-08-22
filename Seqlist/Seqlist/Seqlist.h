#pragma once

#ifdef _MSC_VER									//如果是微软的
#ifdef  LIB_EXPORT							    //如果定义了导出符号
	#define  LIB __declspec(dllexport)
#else
	#define LIB __declspec(dllimport)
#endif
#else 
	#define LIB
#endif

#include <istream>
#include <ostream>
#include <sstream>
#include <iostream>

using namespace std;

template <class T,size_t N>		//size_t = int
class LIB CSeqList
{
private:
	T m_tData[N];				//an array of N number long
	size_t m_nSize;				//the current length of the list 
private:
	//internal interface
	bool IsFull() const;
	bool IsEmpty() const;

public:
	//relationship enum
	enum ERel{
		REL_EQU = 0x01,				// =
		REL_ABOVE = 0x02,			// >
		REL_BELOW = 0x04,			// <
		REL_UNEQUAL = 0x06,			//!=
		REL_MORE = 0x03,			//>=
		REL_LESS = 0x5				//<=
	};
	//logic enum
	enum ESet{
		SET_AND = 0x10,				//A and B
		SET_OR = 0x20,				//A or B
		SET_DEC = 0x40,				//A - B 

	};
public:
	CSeqList();
	CSeqList(const CSeqList<T, N>& obj);
	CSeqList<T,N>& operator =(const CSeqList<T, N>& obj);
	~CSeqList();
	//add
	void push_front(const T& val);						//const & is more efficient;push the data from the head
	void push_back(const T&  val);						//push the data from the end
	inline void insert(size_t index, const T&  val);	//insert from the anywhere between head to end
	CSeqList<T, N>& operator +(const T&  val);			//overload the "+"
	//delete
	void erase(size_t index);							//delete by the index
	//change 
	T& modify(size_t index, const T& val);				//change the data by index
	T& operator [](size_t index);						//change the data by []
	//find
	inline size_t size() const;							//tell the length of the list
	size_t find(const T& val);							//return the size_t index of the data
	//enhancement
	size_t* find_if(ERel rel, const T& val);			//find the arr if condition is ture
	size_t* operator ==(const T& val);						//find the val == index
	size_t* operator >(const T& val);
	size_t* operator <(const T& val);
	size_t* operator !=(const T& val);
	size_t* operator >=(const T& val);
	size_t* operator <=(const T& val);

	size_t* deal(ESet set,size_t* list1, size_t* list2);
	size_t* and(size_t* list1, size_t* list2);
	size_t* or(size_t* list1, size_t* list2);
	size_t* dec(size_t* list1, size_t* list2);
	
	friend istream& operator >> (istream& in, CSeqList<T, N>& obj)
	{
		size_t i;
		obj.m_nSize = 0;
		//T val;
		for (i = 0; i < N; i++)
		{
			if (!(in >> obj.m_tData[i]))
			{
				in.setstate(in.failbit);
				return in;
			}
			obj.m_nSize++;
		}
		return in;
	}
	friend ostream& operator << (ostream& out, CSeqList<T, N>& obj)
	{
		size_t i;
		ostringstream tmp;
		for (i = 0; i < obj.m_nSize; i++)
			tmp << obj.m_tData[i] << " ";
		out << tmp.str();
		return out;
	}
	void Print(size_t *l) const;
};


/*******************************************************************************/
template <class T, size_t N>
CSeqList<T, N>::CSeqList()
	:m_nSize(0)
{
	
}

template <class T, size_t N>
CSeqList<T, N>::CSeqList(const CSeqList<T, N>& obj) //拷贝构造
	:m_nSize(obj.m_nSize)
{
	int i;
	for (i = 0; i < m_nSize; i++)
		m_tDate[i] = obj.m_tDate[i];
}

template <class T, size_t N>
CSeqList<T, N>& CSeqList<T, N>::operator =(const CSeqList<T, N>& obj)
{
	int i;
	m_nSize = obj.m_nSize;
	for (i = 0; i < m_nSize; i++)
		m_tDate[i] = obj.m_tDate[i];
	return *this;
}

template <class T, size_t N>
CSeqList<T, N>::~CSeqList()
{

}


template <class T,size_t N>
size_t CSeqList<T, N>::size() const
{
	return m_nSize;
}

template <class T, size_t N>
bool CSeqList<T, N>::IsFull() const
{
	if (m_nSize == N)						//because i < m_nSize so m_nSize just == N 
		return ture;
	return false;
}

template <class T, size_t N>
bool CSeqList<T, N>::IsEmpty() const
{
	if (m_nSize == 0)
		return true;
	return false;
}

template <class T, size_t N>
void CSeqList<T, N>::push_front(const T& val)						//const & is more efficient;push the data from the head
{
	insert(0, val);
}

template <class T, size_t N>
void CSeqList<T, N>::push_back(const T&  val)						//push the data from the end
{
	insert(m_nSize, val);
}
template <class T, size_t N>
void CSeqList<T, N>::insert(size_t index, const T&  val)				//insert from the anywhere between head to end
{
	if (IsFull() || index >= m_nSize || index < 0)
		return;
	int i;
	for (i = m_nSize; i > index; i--)
		m_tDate[i] = m_tDate[i - 1];
	m_tDate[index] = val;
	m_nSize++;
}

//template <class T, size_t N>
//CSeqList<T, N>& CSeqList<T, N>::operator +(const T&  val)			//overload the "+"
//{
//
//}

template <class T, size_t N>
void CSeqList<T, N>::erase(size_t index)								//delete by the index
{
	if (IsEmpty() ||index <= 0 || index >= m_nSize)
		return;
	int i;
	for (i = index; i < m_nSize - 1; i++)
		m_tDate[i] = m_tDate[i + 1];
	m_nSize--;
}

//change 
template <class T, size_t N>
T& CSeqList<T, N>::modify(size_t index, const T& val)					//change the data by index
{
	/*if (index < 0 || index >)*/
	m_tDate[index] = val;
	return m_tDate[index];
}

template <class T, size_t N>
T& CSeqList<T, N>::operator [](size_t index)							//change the data by []
{
	if (index < 0)
		return m_tDate[0];
	if (index >= m_nSize)
		return m_tDate[m_nSize - 1];
	return m_tDate[index];
}

//find
template <class T, size_t N>
size_t CSeqList<T, N>::find(const T& val)
{
	int i;
	for (i = 0; i < m_nSize; i++)
		if (m_tDate[i] == val)
			return i;

	return -1;
}


template <class T, size_t N>
size_t* CSeqList<T, N>::find_if(ERel rel, const T& val)				//find the arr if condition is ture
{
	size_t i,cnt;
	size_t *p = new size_t[N + 1];
	for (i = 0,cnt = 0; i < m_nSize; i++)
	{
		switch (rel)
		{
		case REL_EQU:
			return this->operator==(val);//if (m_tDate[i] == val)
			//	p[cnt++] = i;
			break;
		case REL_ABOVE:
			return this->operator>(val);/*if (m_tDate[i] > val)
											p[cnt++] = i;*/
			break;
		case REL_BELOW:
			return this->operator<(val);/*if (m_tDate[i] < val)
											p[cnt++] = i;*/
			break;
		case REL_MORE:
			return this->operator>=(val);/*if (m_tDate[i] >= val)
				p[cnt++] = i;*/
			break;
		case REL_LESS:
			return this->operator<=(val);/*if (m_tDate[i] <= val)
				p[cnt++] = i;*/
			break;
		case REL_UNEQUAL:
			return this->operator!=(val);/*if (m_tDate[i] != val)
				p[cnt++] = i;*/
			break;
		}
	}
	p[cnt] = -1;//表示结束
	return p;
}

template <class T, size_t N>
size_t* CSeqList<T, N>::operator ==(const T& val)	
{
	size_t i, cnt;
	size_t *p = new size_t[N + 1];
	for (i = 0, cnt = 0; i < m_nSize; i++)
	{
			if (m_tDate[i] == val)
				p[cnt++] = i;
	}
	p[cnt] = -1;//表示结束
	return p;
}

template <class T, size_t N>
size_t* CSeqList<T, N>::operator >(const T& val)
{
	size_t i, cnt;
	size_t *p = new size_t[N + 1];
	for (i = 0, cnt = 0; i < m_nSize; i++)
	{
		if (m_tData[i] > val)
			p[cnt++] = i;
	}
	p[cnt] = -1;//表示结束
	return p;
}

template <class T, size_t N>
size_t* CSeqList<T, N>::operator <(const T& val)
{
	size_t i, cnt;
	size_t *p = new size_t[N + 1];
	for (i = 0, cnt = 0; i < m_nSize; i++)
	{
		if (m_tData[i] < val)
			p[cnt++] = i;
	}
	p[cnt] = -1;//表示结束
	return p;
}

template <class T, size_t N>
size_t* CSeqList<T, N>::operator !=(const T& val)
{
	size_t i, cnt;
	size_t *p = new size_t[N + 1];
	for (i = 0, cnt = 0; i < m_nSize; i++)
	{
		if (m_tDate[i] != val)
			p[cnt++] = i;
	}
	p[cnt] = -1;//表示结束
	return p;
}

template <class T, size_t N>
size_t* CSeqList<T, N>::operator >=(const T& val)
{
	size_t i, cnt;
	size_t *p = new size_t[N + 1];
	for (i = 0, cnt = 0; i < m_nSize; i++)
	{
		if (m_tDate[i] >= val)
			p[cnt++] = i;
	}
	p[cnt] = -1;//表示结束
	return p;

}

template <class T, size_t N>
size_t* CSeqList<T, N>::operator <=(const T& val)
{
	size_t i, cnt;
	size_t *p = new size_t[N + 1];
	for (i = 0, cnt = 0; i < m_nSize; i++)
	{
		if (m_tDate[i] <= val)
			p[cnt++] = i;
	}
	p[cnt] = -1;//表示结束
	return p;
}

template <class T, size_t N>
size_t* CSeqList<T, N>::deal(ESet set, size_t* list1, size_t* list2)
{
	switch (set)
	{
	case SET_AND:
		return and(list1,list2);
		
	case SET_OR:
		return or(list1, list2);
		
	case SET_DEC:
		return dec(list1, list2);
		
	}
}

template <class T, size_t N>
size_t* CSeqList<T, N>::and(size_t* list1, size_t* list2)
{
	size_t i = 0,j,cnt = 0,* l = new size_t[N];
	while (list1[i] != -1)
	{
		j = 0;
		while (list2[j] != -1)
		{
			if (list1[i] == list2[j])
				l[cnt++] = list[j];
			j++;
		}
		i++;
	}
	list[cnt] = -1;
	return l;
}

template <class T, size_t N>
size_t* CSeqList<T, N>::or(size_t* list1, size_t* list2)
{
	size_t i = 0, j = 0 , cnt = 0, *l = new size_t[N];
	while (list1[i] != -1 && list2[j] != -1)
	{
		if (list2[j] == list1[i])
		{
			l[cnt++] = list1[i];
			i++;
			j++;
		}
		else if (list1[i] < list2[j])
			l[cnt++] = list1[i++];
		else
			l[cnt++] = list2[j++];
	}
	while (list1[i] != -1 || list2[j] != -1)
	{
		if (list1[i] != -1)
			l[cnt++] = list1[i++];
		else
			l[cnt++] = list2[j++];
	}
	l[cnt] = -1;
	return l; 

}

template <class T, size_t N>
size_t* CSeqList<T, N>::dec(size_t* list1, size_t* list2)
{
	bool flag;
	size_t i = 0, j, k, cnt = 0, *l = new size_t[N];
	while (list1[i] != -1)
	{
		j = 0;
		flag = false;
		while (list2[j] != -1)
		{
			if (list1[i] == list2[j])
				i++;
			flag = true;
			break;
		}
		if (!flag)
			l[cnt++] = list1[i];
		i++;
	}
	l[cnt] = -1;
	return l;
}

template <class T, size_t N>
void CSeqList<T, N>::Print(size_t *l) const
{
	size_t i = 0;
	while (l[i] != -1)
	{
		cout << m_tData[l[i]] << " ";
		i++;
	}
	cout << endl;
}