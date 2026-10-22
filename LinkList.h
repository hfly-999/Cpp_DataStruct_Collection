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
		//visit
		void visit()
		{
			std::cout << this << " DNode:" << val << std::endl;

			std::cout << "\t" << prior <<" DNode:" << prior->val << std::endl;

			std::cout << "\t" << next <<" DNode:" << next->val << std::endl;
		}
		friend class list<type>;
	private:
	
		type val;
		DNode* prior;
		DNode* next;
		
	};

};
namespace DSL
{
	//带节点的双向循环链表链表
	template<typename type>
	class list
	{
	public:
		//constructor/copy constructor/desconstructor
		list();							//无参构造
		list(const list& obj);			//拷贝构造
		virtual ~list();				//无参析构

		//add
		void insert(size_t pos, type value);
		void push_back(type value);
		//delete
		void clear();//清空链表
		//find
		bool empty() const;					//链表是否为空	
		void visit()const;					//遍历链表内容
	private:
		static void listfreememory(DNode<type>* start, DNode<type>* end);//释放链内存
		
		size_t length;
		DNode<type>* Head;
	};
	void insertTest();
	void copyconstructTest();
}







#include"LinkList.inl"



