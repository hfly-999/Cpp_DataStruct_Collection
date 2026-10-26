#pragma once
#include"Define.h"

namespace DSL
{
	template<typename type>
	class GenericSqList
	{
	public:
		GenericSqList();
		~GenericSqList();
		
		bool Exchange(unsigned int x, unsigned int y);
		bool IsFull();
		bool IsEmpty();
		bool Insert(type e,unsigned int pos);
		bool Insert(type e);//插入算法，默认插入在顺序表尾部
		int GetLength();
	protected:
		type*			Data;
		unsigned int	length;//1~DEFAULT_HEAP_SIZE-1
		unsigned int	MaxLength;
	};

	enum ENUM_HEAPPATTERN
	{

		Small=1,//小顶堆
		Big=-1,
	};
	template<typename type>
	class GenericHeap :public GenericSqList<type>
	{
	public:
		GenericHeap(int (*cmp)(type A, type B));
		GenericHeap(int (*cmp)(type A, type B), ENUM_HEAPPATTERN pattern);
		~GenericHeap();
		ENUM_HEAPPATTERN pattern;

		bool Push(type e);//比较器默认小顶堆
		bool Pop(type& e);
		type Pop();
	private:
		int (*cmp)(type, type);//比较器指针
	};

}
#include"GenericSqList.inl"
#include"GenericHeap.inl"
