#pragma once
#include"Define.h"
#include"Include.h"

//链表模块
namespace DSL
{
	template<typename type>
	class list;
	
	//链表节点
	template<typename type>
	class DNode
	{
	public:
		//构造
		DNode(
			type value = type{},
			DNode<type>* prior = nullptr,
			DNode<type>* next = nullptr
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
		friend class list<type>;
	private:
	
		type val;
		DNode* prior;
		DNode* next;
		
	};



	//带节点的双向循环链表链表
	template<typename type>
	class list
	{
	public:
		//list容器的迭代器
		class iterator
		{
			DNode<type>* ptr;
		public:
			friend class list;
			iterator(DNode<type>* p = nullptr) :ptr(p) {}
			//it1=it2 over load
			iterator& operator=(const iterator& rhs) { ptr = rhs.ptr; return *this; }
			//*it over load
			type& operator* ()const { return ptr->val; }
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
		//constructor/copy constructor/desconstructor
		list();									//无参构造
		list(std::initializer_list<type> ls);	//有初始化参数列表的构造
		list(const list& obj);					//拷贝构造
		virtual ~list();						//无参析构

		

		//add
		void insert(iterator pos,const type& value);	//插入

		//尾插 
		void push_back(const type& value) { insert(end(), value); }

		//头插
		void push_front(const type &value) { insert(begin(), value); }


		//delete
		void clear();							//清空链表
		void erase(iterator pos);				//删除pos处的元素
		void pop_back() { erase((--end())); }	//尾删
		void pop_front() { erase(begin()); }	//头删
		//find
		void visit()const						//遍历链表内容
		{
			for (auto it = begin(); it != end(); ++it)
				std::cout << *it << std::endl;
		}
		bool empty() const { return !length; }									//链表是否为空	
		size_t size()const { return length; }									//获取链表长度
		iterator begin()const { return iterator(Head->next); }					//获取开始迭代器
		iterator end()const { return iterator(Head); }							//获取尾部迭代器
		const type& front()const { assert(!empty()); return Head->next->val; }	//返回链表第一个元素
		const type& back()const { assert(!empty()); return Head->prior->val; }	//返回链表最后一个元素
		//algorithm
		void reverse();//翻转链表
		//operator over load
		list& operator=(const list& rhs);		//=overload
		//assert
		void check()const;
	private:
		static void listfreememory(DNode<type>* start, DNode<type>* end);//释放链内存
		size_t length;
		DNode<type>* Head;
	};




	void insertTest();
	void copyconstructTest();
	void equalTest();
	void nonparameterconstructorTest();
	void initializer_listconstructorTest();
	void deleteTest();
	void reverseTest();
}








#include"LinkList.inl"



