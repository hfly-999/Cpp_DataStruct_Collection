//顺序表模块
#pragma once
#include"Define.h"//定义
#include"Include.h"//C/C++库

template<typename type>
class SeqList
{
public:
	
	SeqList();											//无参构造
	SeqList(const SeqList& obj);						//拷贝构造函数

	virtual ~SeqList();									//无参析构

	SeqList<type>& operator=(const SeqList<type>& that);//赋值运算符重载
	type& operator[](size_t i);							//[]重载
	type* begin() const;								//获取起始指针
	type* end() const;									//获取尾部指针
	
	//write
	void Insert(type element,size_t position);			//插入到下标为i的地方
	void HeadInsert(type element);						//头插
	void push_back(type element);						//尾插

	//delete
	type Delete(size_t position);						//删除下标为i的元素并且返回val值
	type DeleteTailElement();							//删除尾部元素并返回val值
	type DeleteHeadElement();							//删除头部元素并返回val值
	bool Swap(size_t i, size_t j);						//交换i与j下标的元素
	//find
	type Find(size_t i)const;							//查找
	size_t Getsize() const;								//获取顺序表长度
	void Visit() const;									//使用迭代器遍历顺序表
	size_t GetCapacity()const;							//计算当前应该的容量
	
	
	
	void AllocMoreMemory(size_t NewCapacity=0);		//
	void AllocLessMemory(size_t NewCapacity=0);		//
	
protected:

	size_t size;
	size_t Capacity;
	type* Data;



};
#include"SeqList.inl"

void SeqListInsertTest();						//顺序表各种插入功能的测试
void SeqListDeleteTest();						//顺序表各种删除功能的测试
void SeqListSwapTest();							//交换i与j下标的元素功能测试
void SeqListCopyTest();							//深拷贝测试
void SeqListIteratorTest();						//顺序表使用迭代器测试
void SeqListCopyConstructorTest();				//拷贝构造函数测试
void SeqListEqualOverLoadTest();				//=重载测试

