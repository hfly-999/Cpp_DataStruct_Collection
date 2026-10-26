#include"Queue.h"
										
namespace DSL
{
//--------------------------------------------------------//
/*
*		DataStruct-Queue(·ºÐÍ¶ÓÁÐ)
*
*		Created by HFLY
*
*				---time:2026.6.3
*
*/
//--------------------------------------------------------//
	template<typename type>
	GenericQueue<type>::GenericQueue()
	{
		Data = new type[DEFAULT_QUEUE_SIZE];
		rear = 0;
		front = 0;
		DefaultSize = DEFAULT_QUEUE_SIZE;
		mallocSize = DEFAULT_QUEUE_SIZE;
	}


	template<typename type>
	GenericQueue<type>::~GenericQueue()
	{
		delete Data;
	}


	template<typename type>
	bool GenericQueue<type>::EnQueue(type e)
	{
		if (IsFull() == false)
		{
			Data[rear++] = e;
			rear %= mallocSize;
			return true;
		}
		return false;
	}


	template<typename type>
	bool GenericQueue<type>::DeQueue(type& e)
	{
		if (IsEmpty() == false)
		{
			e = Data[front++];
			front %= mallocSize;
			return true;

		}
		return false;
	}


	template<typename type>
	bool GenericQueue<type>::IsFull()
	{
		if ((rear + 1) % mallocSize == front)return true;
		return false;
	}


	template<typename type>
	bool GenericQueue<type>::IsEmpty()
	{
		if (rear == front)return true;
		return false;
	}


	template<typename type>
	unsigned int GenericQueue<type>::GetLength()
	{
		return (rear + DEFAULT_QUEUE_SIZE - front) % DEFAULT_QUEUE_SIZE;
	}
}