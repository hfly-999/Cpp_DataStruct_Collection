//#pragma once
//#include"SeqList.h"
//#include"list.h"
//namespace DSL
//{
//	/*---------------------------------------------------------------*/
//	//顺序栈
//	template<typename type>
//	class Stack
//	{
//	public:
//		//栈的无参构造函数
//		Stack();
//		//栈的拷贝构造函数
//		Stack(const Stack& obj);
//		//栈的无参析构函数
//		~Stack();
//		//出栈
//		void pop();
//		//查询栈顶元素
//		type top()const;
//		//入栈
//		void push(type element);
//		//栈是否为空
//		bool empty() const;
//		
//		//获取栈的深度
//		size_t GetDepth()const;
//		type GetTop() const;//获取栈顶元素
//	private:
//		SeqList<type>L;
//	};
//	/*---------------------------------------------------------------*/
//	//链式栈
//	
//	template<typename type>
//	class LStack
//	{
//	public:
//		//栈的无参构造函数
//		LStack();
//		//栈的拷贝构造函数
//		LStack(const LStack& obj);
//		//栈的无参析构函数
//		~LStack();
//		//出栈
//		void pop();
//		//查询栈顶元素
//		const type top()const;
//		//入栈
//		void push(type element);
//		//获取栈的深度
//		size_t GetDepth()const;
//		//栈是否为空
//		bool empty()const;
//		type GetTop()const;//获取栈顶元素
//	private:
//		list<type>L;
//	};
//	/*---------------------------------------------------------------*/
//}
//#include"Stack.inl"
////顺序栈的功能测试
//void StackTest();
////顺序栈的拷贝构造函数测试
//void StackCopyConstructorTest();
////链式栈的拷贝构造函数测试
//void LStackCopyConstructorTest();
