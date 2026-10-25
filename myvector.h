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

		//无参构造
		vector() :
			Size(0),
			Capacity(0),
			Data(nullptr)
		{
		}
		//初始化参数列表,构造
		vector(const std::initializer_list<type> ls) :
			Size(0),
			Capacity(calcapacity(ls.size())),
			Data((type*)::operator new(sizeof(type)* Capacity))//只申请内存,不调用构造
		{
			for (auto it = ls.begin(); it != ls.end(); ++it)
			{
				push_back(*it);
			}

		}
		//拷贝构造
		vector(const vector& obj) :
			Size(0),
			Capacity(obj.Capacity),
			Data((type*)::operator new(sizeof(type)* Capacity))//只申请内存,不调用构造
		{
			for (auto it = obj.begin(); it != obj.end(); ++it)
			{
				new (Data + Size)type(*it);//在地址进行构造
				Size++;
			}
		}


		//虚析构
		virtual ~vector()
		{
			check();
			for (size_t i = 0; i < Size; i++)
				Data[i].~type();//在地址上调用析构
			::operator delete (Data);//回收内存
		}


		//over load
		vector& operator=(const vector& rhs)
		{
			if (this == &rhs)return *this;
			clear();//清空数组元素
			for (auto it = rhs.begin(); it != rhs.end(); ++it)
			{
				if (full())reallocate();//扩容
				new (Data + Size)type(*it);//在地址上进行构造
				Size++;
			}
			check();
			return *this;
		}//拷贝赋值
		type& operator[](size_t index)
		{
			assert(index < Size);
			return Data[index];
		}//可以修改的版本
		const type& operator[](size_t index)const
		{
			assert(index < Size);
			return Data[index];
		}//不可以修改的版本

		//获取迭代器
		type* begin(){ return Data; }//允许修改的版本
		const type* begin()const { return Data; }//不允许修改的版本

		type* end() { return Data + Size; }
		const type* end()const { return Data + Size; }//不允许修改的版本


		//insert
		//插入
		void insert(type* pos,const type& value)
		{
			size_t i = pos - Data;//计算插入下标;
			assert(i <= Size);//插入位置非法
			if (full())reallocate();//扩容
			for (size_t j = Size; j != i; j--)
			{
				new (Data + j)type(Data[j - 1]);//进行type拷贝构造
				Data[j - 1].~type();//析构
			}
			new (Data + i)type(value);//插入处进行构造
			Size++;//维护size
			
		}
		void push_back(const type &value) 
		{ 
			insert(end(), value);
		}
		void push_front(const type& value)
		{
			insert(begin(), value);
		}



		//find
		bool empty()const { return Size == 0; }
		size_t capacity()const { return Capacity; }
		size_t size()const { return Size; }
		type back()const
		{
			assert(!empty());
			return Data[Size - 1];
		}
		type front()const
		{
			assert(!empty());
			return Data[0];
		}

		//delete
		//清空vector
		void clear()
		{
			while (Size)
			{
				Data[Size - 1].~type();//执行析构,这一步不会释放内存
				Size--;
			}
		}
		


		
	private:

		//check
		void check()
		{

			assert(Size <= Capacity);
		}
		//扩容
		void reallocate()
		{
			Capacity = calcapacity(Capacity);//重新申请更大容量,倍率1.5
			type* new_memory = (type*)::operator new(sizeof(type) * Capacity);//申请新内存
			for (size_t i = 0; i < Size; i++)
			{
				new (new_memory + i)type(Data[i]);//在内存上进行拷贝构造
			}
			for (size_t i = 0; i < Size; i++)
			{
				Data[i].~type();//顺序析构
			}
			::operator delete(Data);
			Data = new_memory;

		}
		//计算需要容量
		bool full()const { return Size == Capacity; }

		static size_t calcapacity(size_t sz) { return	sz <= 1 ? 2 : sz + sz / 2; }
	};

	void Test();


}




