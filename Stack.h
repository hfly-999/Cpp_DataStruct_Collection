#pragma once
#include"Define.h"
#include"Tree.h"
//顺序栈
typedef struct SeqStack
{
	ElemType* data;
	int top;
	int base;
}SeqStack;





//链栈(不需要头结点)
typedef struct StackNode
{
	ElemType data;
	StackNode* next;
}*LinkStack,StackNode;


/*--------------------------------------------------------------------------------------*/

class Stack
{
public:
	
	Stack()
	{
		this->top = this->base = 0;
	}
	bool Push(void *e)
	{
		if (this->top == MAXSIZE)return false;
		this->data[this->top++] = e;
		return true;
	}
	void* Pop()
	{
		if (this->IsEmpty() == false)
		{
			void* ret = this->data[--this->top];
			this->data[this->top] = NULL;
			return ret;
		}
		return NULL;
	}
	bool IsEmpty()
	{
		if (this->top == this->base)return true;
		return false;
	}
	void Print()
	{
		for (int i = this->top; i != this->base; i--)
		{
			printf("%p ", this->data[i - 1]);

		}
		cout << endl;
	}


	void* data[MAXSIZE];
	int		top,
			base;

};




/*--------------------------------------------------------------------------------------*/
//基础操作
/*初始化线性栈*/
bool Init(SeqStack& S);
/*入线性栈*/
bool Push(SeqStack& S, ElemType e);
/*出线性栈*/
bool Pop(SeqStack& S, ElemType& e);
/*打印线性栈*/
void Print(SeqStack S);
/*判断顺序栈是否为空*/
bool IsEmpty(SeqStack S);
/*求线性栈的长度*/
unsigned int SeqStackGetLength(SeqStack S);
/*清空线性栈*/
void ClearSeqStack(SeqStack S);
/*销毁线性栈*/
void Destroy(SeqStack S);

/*初始化链栈*/
bool Init(LinkStack& S);

/*入链栈*/
bool Push(LinkStack& S, ElemType e);

/*打印链栈*/
void Print(LinkStack S);

/*出链栈*/
bool Pop(LinkStack& S, ElemType &e);
/*--------------------------------------------------------------------------------------*/