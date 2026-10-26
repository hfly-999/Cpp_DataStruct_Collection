#pragma once
#include"Define.h"


namespace DSL
{
	template<typename type>
	class GenericQueue//ElemType类型的队列
	{
	public:
		//存储ElemType类型的队列的构造函数
		GenericQueue();
		//存储ElemType类型的队列的析构函数
		~GenericQueue();
		//入队列
		bool EnQueue(type e);
		//出队列
		bool DeQueue(type& e);
		//队列是否为满，满返回true，不满返回false
		bool IsFull();
		//队列是否为空，空返回true，不空返回false
		bool IsEmpty();
		//获取队列长度
		unsigned int GetLength();
	
	private:
		//数据指针
		type* Data;
		//队尾指针
		unsigned int rear;
		//队头指针
		unsigned int front;
		//默认队列的大小 单位：sizeof(type)*B
		unsigned int DefaultSize;
		//已经申请的大小 单位：sizeof(type)*B
		unsigned int mallocSize;
	};

	
}
#include"Queue.inl"

