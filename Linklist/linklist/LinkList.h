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


#include<initializer_list>									//C++ 11之后有的初始化列表，[]中括号的赋值方式

template<class T>
class LIB CLinkList
{
private:
	T m_tData;
	CLinkList *m_pNext;										//the point to the next obj
	size_t m_nLen;											//the length of the Linklist	从当前节点开始到末尾节点结束的长度

public:
	CLinkList(T val);
	CLinkList(std::initializer_list<T> l);       //这种C++自带的初始化方式，来构造链表。支持定义的时候就立刻初始化
	//拷贝构造、赋值构造要（深拷贝）此处不写了
	~CLinkList();

private:
	bool  operator !=(CLinkList<T>& obj);					//内部关系的判断，重载！=符号

	//bool  operator ==(CLinkList<T>& obj);					//内部关系的判断，重载==符号
	
public:
	void push_back(const T& val);							//尾插法
	void insert(int nIndex, const T& val);					//插入
	void insert(CLinkList<T>& pos, const T& val);			//插入
	T& operator [](int nIndex);								//修改
	CLinkList<T>& GetObj(int nIndex);						//获取对象
	void print() const;										//打印
	inline size_t size() const;								//当前对象的长度获取
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
	delete m_pNext;						//递归调用了析构函数，可以一层一层的析构下去
	m_pNext = nullptr;
}

template<class T>
bool  CLinkList<T>::operator !=(CLinkList<T>& obj)				//重载！=符号
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
		cout << "Warning : 数组下标越界 ！";
		return *this;
	}
	size_t i;
	auto p = this;
	for (i = 0; i < nIndex; i++)
		p = p->m_pNext;
	return *p;
}

template<class T>
void CLinkList<T>::push_back(const T& val)//尾插法
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
void CLinkList<T>::insert(int nIndex, const T& val)					//插入
{
	auto p = GetObj(nIndex);								//找到你要插入的位置Index节点
	if (p != *this)
	{
		size_t nBak;
		auto ptr = this;
		auto pTail = p.m_pNext;										//从中间剪断,保存断口末尾的链表
		p.m_pNext = new CLinkList<T>(val);								//给剪断的地方添加一个新的链表量
		while (ptr != p.m_pNext)										//此处是在更新前面节点的长度值
		{
			nBak = ++ptr->m_nLen;
			ptr = ptr->m_pNext;
		}
		ptr->m_nLen = nBak - 1;
		ptr->m_pNext = pTail;											//前后的节点连接起来
	}
	else
	{
		cout << "错误：数组下标越界！";
		return;
	}


}

template<class T>
void CLinkList<T>::insert(CLinkList<T>& pos, const T& val)
{
	auto p = this;
	while (*p != pos && !p)//这里的！=符号要进行重载，因为这是一个新的类型，不能简单的定义这个！=符号，要写一写重载
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
T& CLinkList<T>::operator [](int nIndex)								//修改
{
	if (nIndex >= m_nLen)
	{
		cout << "Warning : 数组下标越界 ！";
		return this->m_tData;
	}
	size_t i;
	auto p = this;
	for (i = 0; i < nIndex; i++)
		p = p->m_pNext;
	return p->m_tData;
}
template<class T>
void CLinkList<T>::print()	const										//打印
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