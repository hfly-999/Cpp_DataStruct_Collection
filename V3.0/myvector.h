//vector模块
#pragma once
#include"Define.h"//定义
#include"Include.h"//C/C++库
namespace DSL
{
	template<typename Type>
	class vector
	{
		size_t Size;
		size_t Capacity;
		Type* Data;
	public:

		//无参构造
		vector() :
			Size(0),
			Capacity(0),
			Data(nullptr)
		{
		}
		//初始化参数列表,构造
		vector(const std::initializer_list<Type> ls) :
			Size(0),
			Capacity(calcapacity(ls.size())),
			Data((Type*)::operator new(sizeof(Type)* Capacity))//只申请内存,不调用构造
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
			Data((Type*)::operator new(sizeof(Type)* Capacity))//只申请内存,不调用构造
		{
			for (auto it = obj.begin(); it != obj.end(); ++it)
			{
				new (Data + Size)Type(*it);//在地址进行构造
				Size++;
			}
		}


		//虚析构
		virtual ~vector()
		{
			check();
			for (size_t i = 0; i < Size; i++)
				Data[i].~Type();//在地址上调用析构
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
				new (Data + Size)Type(*it);//在地址上进行构造
				Size++;
			}
			check();
			return *this;
		}//拷贝赋值

		Type& operator[](size_t index)
		{
			assert(index < Size);
			return Data[index];
		}//可以修改的版本

		const Type& operator[](size_t index)const
		{
			assert(index < Size);
			return Data[index];
		}//不可以修改的版本

		//获取迭代器
		Type* begin(){ return Data; }//允许修改的版本
		const Type* begin()const { return Data; }//不允许修改的版本

		Type* end() { return Data + Size; }
		const Type* end()const { return Data + Size; }//不允许修改的版本


		//insert
		//插入
		void insert(Type* pos,const Type& value)
		{
			Type tmp = value;//拷贝value的副本,防止自赋值导致value被改变
			size_t i = pos - Data;//计算插入下标;
			assert(i <= Size);//插入位置非法
			if (full())reallocate();//扩容
			
			new (Data + Size)Type();//执行构造
			for (size_t j = Size; j != i; --j)		
				Data[j] = Data[j - 1];//拷贝赋值
			Data[i]=tmp;//拷贝赋值
			Size++;//维护size
			check();
		}
		void push_back(const Type &value) 
		{ 
			insert(end(), value);
		}
		void push_front(const Type& value)
		{
			insert(begin(), value);
		}



		//find
		bool empty()const { return Size == 0; }
		size_t capacity()const { return Capacity; }
		size_t size()const { return Size; }
		Type& back()
		{
			assert(!empty());
			return Data[Size - 1];
		}
		const Type& back()const
		{
			assert(!empty());
			return Data[Size - 1];
		}

		Type& front()
		{
			assert(!empty());
			return Data[0];
		}
		const Type& front()const
		{
			assert(!empty());
			return Data[0];
		}


		//delete
		void clear()
		{
			while (Size)
			{
				Data[Size - 1].~Type();//执行析构,这一步不会释放内存
				Size--;
			}
		}
		void pop_back()
		{
			erase(end()-1);
		}
		void erase(Type* pos)
		{

			size_t i = pos - begin();
			assert(i < Size);
			for (size_t j = i + 1; j < Size; ++j)
				Data[j - 1] = Data[j];
			Data[Size - 1].~Type();
			Size--;//维护Size
		}
		void erase(Type* first, Type* last)
		{
			size_t i = first - begin();
			size_t j = last - begin();
			assert(i < Size);
			assert(j <= Size);
			size_t count = j - i;
			while (count--)
				erase(first);
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
			Type* new_memory = (Type*)::operator new(sizeof(Type) * Capacity);//申请新内存
			for (size_t i = 0; i < Size; i++)
			{
				new (new_memory + i)Type(Data[i]);//在内存上进行拷贝构造
			}
			for (size_t i = 0; i < Size; i++)
			{
				Data[i].~Type();//顺序析构
			}
			::operator delete(Data);
			Data = new_memory;

		}
		//计算需要容量
		bool full()const { return Size == Capacity; }

		static size_t calcapacity(size_t sz) { return	sz <= 1 ? 2 : sz + sz / 2; }
	};

	void vector_pop_back_test()
	{
		vector<int>v = { 1,2,3,4 };
		v.pop_back();
		for (auto it = v.begin(); it != v.end(); ++it)
			std::cout << *it << std::endl;
	}
	void vector_insert_test()
	{
		vector<std::string>v;
		v.insert(v.begin(), "LIWEI");
		v.insert(v.begin(), "HFLY");
		v.insert(v.begin(), "TIAN GUI");
		v.insert(v.begin(), "THE SHY");
		v.insert(v.begin(), "YASUO");
		for (auto it = v.begin(); it != v.end(); ++it)
			std::cout << *it << std::endl;
	}
	void vector_erase_test()
	{
		vector<std::string>v;
		v.insert(v.begin(), "LIWEI");
		v.insert(v.begin(), "HFLY");
		v.insert(v.begin(), "TIAN GUI");
		v.insert(v.begin(), "THE SHY");
		v.insert(v.begin(), "YASUO");
		v.erase(v.begin() + 1, v.end() - 1);
		for (auto it = v.begin(); it != v.end(); ++it)
			std::cout << *it << std::endl;
		//"LIWEI"
		//"YASUO"
	}
	

}




