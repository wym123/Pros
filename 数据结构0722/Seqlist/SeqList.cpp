
#include "SeqList.h"
using namespace std;
template <class T, size_t N>
CSeqList<T, N>::CSeqList()
{

}
template <class T, size_t N>
CSeqList(const CSeqList<T, N>& obj);					//拷贝构造

template <class T, size_t N>
CSeqList<T, N>& operator =(const CSeqList<T, N>& obj);	//赋值构造

template <class T, size_t N>
CSeqList::~CSeqList()
{

}

template <class T, size_t N>
bool IsFull() const;

template <class T, size_t N>
bool IsEmpty() const;

// 增
template <class T, size_t N>
void push_front(const T& val);					// 头插法

template <class T, size_t N>
void push_back(const T& val);					// 尾插法

template <class T, size_t N>
CSeqList<T, N>& operator +(const T& val);		// 尾插法的运算符重载
// 删
void erase(size_t index);						// 根据下标删除
// 改
T& modify(size_t index, const T& val);			// 根据下标修改
T& operator [](size_t index);					// 下标访问


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