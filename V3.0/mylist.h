#pragma once
#include"Define.h"
#include"Include.h"

//链表模块
namespace DSL
{
	template<typename Type>
	class list;
	
	//链表节点
	template<typename Type>
	class DNode
	{
	public:
		//构造
		DNode(
			Type value = Type{},
			DNode<Type>* prior = nullptr,
			DNode<Type>* next = nullptr
		) :
			val(value),
			prior(prior),
			next(next)
			{};
		//拷贝构造
		DNode(const DNode& obj) :
			val(obj.val),
			prior(nullptr),
			next(nullptr){};
		//析构
		~DNode() = default;
		friend class list<Type>;
	private:
	
		Type val;
		DNode* prior;
		DNode* next;
		
	};



	//带节点的双向循环链表链表
	template<typename Type>
	class list
	{
	public:
		//list容器的迭代器
		class iterator
		{
			DNode<Type>* ptr;
		public:
			friend class list;
			iterator(DNode<Type>* p = nullptr) :ptr(p) {}
			//*it over load
			Type& operator* ()const { return ptr->val; }
			//it++
			iterator operator++(int)
			{
				iterator old = *this;
				ptr = ptr->next;
				return old;
			}
			//++it
			iterator& operator++()
			{
				ptr = ptr->next;
				return *this;
			}
			//it--
			iterator operator--(int)
			{
				iterator old = *this;
				ptr = ptr->prior;
				return old;
			}
			//--it
			iterator& operator--()
			{
				ptr = ptr->prior;
				return *this;
			}
			//it==it
			bool operator==(const iterator& rhs)const { return ptr == rhs.ptr; }
			//it!=it
			bool operator!=(const iterator& rhs)const { return !(*this == rhs); }

		};
		//const list&容器的迭代器
		class const_iterator
		{
			DNode<Type>* ptr;
		public:
			friend class list;
			const_iterator(DNode<Type>* p = nullptr) :ptr(p) {}
			//*it
			const Type& operator*()const { return ptr->val; }
			//++it
			const_iterator& operator++()
			{
				ptr = ptr->next;
				return *this;
			}
			//it++
			const_iterator operator++(int)
			{
				const_iterator old = ptr;
				ptr = ptr->next;
				return old;
			}
			//--it
			const_iterator& operator--()
			{
				ptr = ptr->prior;
				return *this;
			}
			//it--
			const_iterator operator--(int)
			{
				const_iterator old = ptr;
				ptr = ptr->prior;
				return old;
			}
			//it==it
			bool operator==(const const_iterator& rhs) const { return ptr == rhs.ptr; }
			//it!=it
			bool operator!=(const const_iterator& rhs) const { return !(*this == rhs); };
		};

		//const list&容器的迭代器

		//constructor/copy constructor/desconstructor
		list();									//无参构造
		list(std::initializer_list<Type> ls);	//有初始化参数列表的构造
		list(const list& obj);					//拷贝构造
		virtual ~list();						//无参析构



		//add
		void insert(iterator pos, const Type& value);	//插入

		//尾插 
		void push_back(const Type& value) { insert(end(), value); }

		//头插
		void push_front(const Type& value) { insert(begin(), value); }


		//delete
		void clear();							//清空链表
		void erase(iterator pos);				//删除pos处的元素	
		void pop_back() 
		{ 
			assert(!empty());
			erase(--end());
		}	//尾删
		void pop_front() 
		{ 
			assert(!empty());
			erase(begin());
		
		}	//头删
		//find
		void visit()const									//遍历链表内容
		{
			for (auto it = begin(); it != end(); ++it)
				std::cout << *it << std::endl;
		}
		bool empty() const			{ return !length; }						//链表是否为空	
		size_t size()const			{ return length; }						//获取链表长度
		iterator begin()			{ return iterator(Head->next); }		//获取开始迭代器
		const_iterator begin()const { return const_iterator(Head->next); }	//获取开始迭代器const
		iterator end()				{ return iterator(Head); }				//获取尾部迭代器
		const_iterator end()const	{ return const_iterator(Head); }		//获取尾部迭代器const
		Type& front()				{ assert(!empty()); return Head->next->val; }
		const Type& front()const	{ assert(!empty()); return Head->next->val; }	//返回链表第一个元素
		Type& back()				{ assert(!empty()); return Head->prior->val; }	//返回链表的最后一个元素
		const Type& back()const		{ assert(!empty()); return Head->prior->val; }	//返回链表最后一个元素
		//algorithm
		void reverse();//翻转链表
		//operator over load
		list& operator=(const list& rhs);		//=overload
		//assert
		void check()const;
	private:
		static void listfreememory(DNode<Type>* start, DNode<Type>* end);//释放链内存
		size_t length;
		DNode<Type>* Head;
	};




	void insertTest();
	void copyconstructTest();
	void equalTest();
	void nonparameterconstructorTest();
	void initializer_listconstructorTest();
	void deleteTest();
	void reverseTest();
}








#include"mylist.inl"



