#pragma once
#include"Define.h"

namespace DSL
{
	template<typename type>
	class GenericStack//泛型栈
	{
	public:
		//泛型栈的构造函数
		GenericStack<type>();

		//泛型栈的析构函数
		~GenericStack<type>();


		//入栈
		bool Push(type e);//


		//出栈
		bool Pop(type& e);


		//是否为空，为空返回true，不为空返回false
		bool IsEmpty();


		//是否栈满，栈满返回true，不满返回false
		bool IsFull();


		//取得栈顶元素
		type GetTop();


		//栈的数据区
		type* Data;


		//栈顶指针
		unsigned int top;


		//栈底指针
		unsigned int base;

	private:
		//栈的默认大小/sizeof(ElemType)
		unsigned int DefaultSize;


		//栈已经申请的空间大小/sizeof(ElemType)
		unsigned int mallocSize;
	};

}

#include"Stack.inl"





