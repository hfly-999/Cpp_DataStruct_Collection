//vector模块
#pragma once
#include"Define.h"//定义
#include"Include.h"//C/C++库
namespace DSL
{
	template<typename type>
	class vector
	{
		size_t Size;
		size_t Capacity;
		type* Data;
	public:
		vector(const std::initializer_list<type> ls) :
			Size(0),
			Capacity(calcapacity(ls.size())),
			Data((type*)::operator new(sizeof(type)* Capacity))//只申请内存,不调用构造
		{
			for (auto it = ls.begin(); it != ls.end(); ++it)
			{
				new (Data + Size)type(*it);//在地址上调用构造
				Size++;
			}
				
		}
		virtual ~vector()
		{
			for (size_t i = 0; i < Size; i++)
				Data[i].~type();//在地址上调用析构
			::operator delete (Data);//回收内存
		}
		
		//insert
		void insert(type* pos, type& value)
		{
		
		}
		//扩容
		void reallocate()
		{
			Capacity = calcapacity(Capacity);//重新申请更大容量,倍率1.5
			type* new_memory = (type*)::operator new(sizeof(type) * Capacity);
			for (size_t i = 0; i < Size; i++)
			{
				new (new_memory + i)type(Data[i]);//拷贝构造
			}
			for (size_t i = 0; i < Size; i++)
			{
				Data[i].~type();//顺序析构
			}
			::operator delete(Data);
			Data = new_memory;

		}
		void push_back(type value) { insert(Data + Size, value); }
		size_t capacity()const { return Capacity; }
		size_t size()const { return Size; }
		static size_t calcapacity(size_t sz) { return sz + sz / 2; }
	};



}




