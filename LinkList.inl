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
	template<typename type>
	list<type>::list(std::initializer_list<type> ls):
		length(0),
		Head(new DNode<type>())
	{
		//set loop list
		Head->next = Head;
		Head->prior = Head;
		for (auto it = ls.begin(); it != ls.end(); ++it)
			push_back(*it);
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
	void list<type>::insert(iterator pos, type value)
	{
		
		DNode<type>* next_node = pos.ptr;
		
		DNode<type>* new_node 
			= new DNode<type>(value,next_node->prior,next_node);//malloc
		
		next_node->prior->next = new_node;
		next_node->prior = new_node;
		length++;
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
	//删除节点
	template<typename type>
	void list<type>::erase(iterator pos)
	{
		assert(pos != end());
		DNode<type>* node = pos.ptr;
		node->prior->next = node->next;
		node->next->prior = node->prior;
		delete node;
		length--;
	}
	//algoritm
	//翻转链表
	template<typename type>
	void list<type>::reverse()
	{
		DNode<type>* node = Head;
		do
		{
			DNode<type>* tmp = node->next;
			node->next = node->prior;
			node->prior = tmp;
			node = node->prior;
		} while (node != Head);
	}


	//operator over load
	
	template<typename type>
	list<type>& list<type>::operator=(const list<type>& rhs)
	{
		if (this == &rhs)return *this;//自赋值处理
		clear();//清空链表
		for (auto it = rhs.begin(); it != rhs.end(); ++it)
			push_back(it.ptr->val);
		return *this;
	}
	//assert
	template<typename type>
	void list<type>::check()
	{
		if (length == 0)
		{
			assert(Head != nullptr);
			assert(Head->next == Head);
			assert(Head->prior == Head);
		}
		else
		{
			size_t n = 0;
			for (DNode<type> *p = Head->next; p != Head; p=p->next)
			{
				assert(p->next->prior == p);
				n++;
				assert(n <= length);
			}
			assert(n == length);
			n = 0;
			for (DNode<type>* p = Head->prior; p != Head; p = p->prior)
			{
				assert(p->prior->next==p);
				n++;
				assert(n <= length);
			}
			assert(n == length);

		}
	}
	//static
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