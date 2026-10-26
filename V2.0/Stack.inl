#include"Stack.h"

namespace DSL
{
//----------------------------------------------------//
/*
*	template<type>class GenericStack(·ºÐÍÕ»)
*
*								------time2026.6.3
*								------Created by HFLY
*/

	template<typename type>
	GenericStack<type>::GenericStack()
	{
		Data = new type[DEFAULT_STACK_SIZE];
		top = base = 0;
		mallocSize = DefaultSize = DEFAULT_STACK_SIZE;
	}


	template<typename type>
	GenericStack<type>::~GenericStack()
	{
		delete Data;
	}


	template<typename type>
	bool GenericStack<type>::Push(type e)
	{
		if (IsFull() == true)return false;
		Data[top++] = e;
		return true;
	}


	template<typename type>
	bool GenericStack<type>::Pop(type& e)
	{
		if (IsEmpty() == true)return false;
		e = Data[--top];
		return true;
	}


	template<typename type>
	bool GenericStack<type>::IsEmpty()
	{
		if (top == 0)return true;
		return false;
	}


	template<typename type>
	bool GenericStack<type>::IsFull()
	{
		if (top == DEFAULT_STACK_SIZE)return true;
		return false;
	}


	template<typename type>
	type GenericStack<type>::GetTop()
	{
		if (IsFull() == true)
			return (type)DEFAULT_MAX_SHORT;
		return Data[top - 1];
	}


}