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
	//内部接口
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
	//逻辑枚举
	enum ESet
	{
		SET_AND = 0x01, 
		SET_OR = 0x20,
		SET_DEC = 0x40
	};

public:
	CSeqList();
	CSeqList(const CSeqList<T, N>& obj);					//拷贝构造
	CSeqList<T, N>& operator =(const CSeqList<T, N>& obj);	//赋值构造
	~CSeqList();
	// 增
	void push_front(const T& val);					// 头插法
	void push_back(const T& val);					// 尾插法
	inline void insert(int index, const T& val);	// 插入
	CSeqList<T, N>& operator +(const T& val);		// 尾插法的运算符重载
	// 删
	void erase(size_t index);						// 根据下标删除
	// 改
	T& modify(size_t index, const T& val);			// 根据下标修改
	T& operator [](size_t index);					// 下标访问
	// 查
	inline size_t size() const;						// 查询长度
	size_t find(const T& val);						// 按值查找
	// 增强型关系查找函数
	size_t* find_if(ERel rel, const T& val);		// 查询符合关系条件的数组
	size_t* operator ==(const T& val);				// 查询等于这个数值的下标
	size_t* operator >(const T& val);				// 查询大于这个数值的下标
	size_t* operator <(const T& val);				// 查询小于这个数值的下标
	size_t* operator !=(const T& val);				// 查询不等于这个数值的下标
	size_t* operator >=(const T& val);				// 查询大于或等于这个数值的下标
	size_t* operator <=(const T& val);				// 查询小于或等于这个数值的下标
	// 增强型的逻辑处理函数
	size_t* deal(ESet set, size_t* list1, size_t* list2);	// 集合处理	
	size_t* and(size_t* list1, size_t* list2);				// 交集
	size_t* operator &&(size_t* l);
	size_t* or(size_t* list1, size_t* list2);				// 并集
	size_t* operator ||(size_t* l);
	size_t* dec(size_t* list1, size_t* list2);				// 差集
	size_t* operator -(size_t* l);
	// 增强型增删改
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
size_t CSeqList<T, N>::size() const					// 查询长度
{

}