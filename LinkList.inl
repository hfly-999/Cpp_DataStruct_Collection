#include"LinkList.h"
namespace DSL
{
	//constructor
	template<typename type>
	list<type>::list() :
		length(0),
		Head(new DNode<type>())
	{
		//set loop list
		Head->next = Head;
		Head->prior = Head;
	}
	//copy constructor
	template<typename type>
	list<type>::list(const list<type>& obj) :
		length(0),
		Head(new DNode<type>())//申请头结点内存
	{
		//set loop list
		Head->next = Head;
		Head->prior = Head;
		DNode<type>* obj_node = obj.Head->next;
		while (obj_node != obj.Head)
		{
			push_back(obj_node->val);
			obj_node = obj_node->next;
		}
	}
	//deconstructor
	template<typename type>
	list<type>::~list()
	{
		//free Link memory
		if(!empty())
			list::listfreememory(Head,Head->prior);
	}
	//add
	template<typename type>
	void list<type>::insert(size_t pos, type value)
	{
		assert(pos <= length);
		DNode<type>* pre_node = Head;
		while (pos--)
			pre_node = pre_node->next;
		DNode<type>* new_node 
			= new DNode<type>(value,pre_node,pre_node->next);//malloc
		pre_node->next->prior = new_node;
		pre_node->next = new_node;
		length++;
	}
	template<typename type>
	void list<type>::push_back(type value)
	{
		insert(length, value);
	}

	//delete
	//清空链表
	template<typename type>
	void list<type>::clear()
	{
		if (!empty())
			list::listfreememory(Head->next, Head->prior);//释放除头结点外的所有节点
		length = 0;//维护length
	}
	//find
	//判空
	template<typename type>
	bool list<type>::empty() const
	{
		return 
			Head->next == Head 
			&&
			Head->prior == Head;
	}
	//遍历访问
	template<typename type>
	void list<type>::visit()const
	{
		DNode<type>* node = Head->next;
		while (node != Head)
		{
			node->visit();
			node = node->next;
		}
	}



	template<typename type>
	void list<type>::listfreememory(DNode<type>* start,DNode<type>* end)
	{
		assert(start != nullptr && end != nullptr);
		start->prior->next = end->next;
		end->next->prior = start->prior;
		while (start != end)
		{
			DNode<type>* next = start->next;
			std::cout << start << " DNode\t" << start->val << "\thas been free\n";
			delete start;
			start = next;
		}
		std::cout << start << " DNode\t" << start->val << "\thas been free\n";
		delete start;
	}
	
};