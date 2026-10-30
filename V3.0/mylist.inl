#include"mylist.h"
namespace DSL
{
	//constructor
	template<typename Type>
	list<Type>::list() :
		length(0),
		Head(new DNode<Type>())
	{
		//set loop list
		Head->next = Head;
		Head->prior = Head;
	}
	template<typename Type>
	list<Type>::list(std::initializer_list<Type> ls):
		length(0),
		Head(new DNode<Type>())
	{
		//set loop list
		Head->next = Head;
		Head->prior = Head;
		for (auto it = ls.begin(); it != ls.end(); ++it)
			push_back(*it);
	}
	//copy constructor
	template<typename Type>
	list<Type>::list(const list<Type>& obj) :
		length(0),
		Head(new DNode<Type>())//申请头结点内存
	{
		//set loop list
		Head->next = Head;
		Head->prior = Head;
		DNode<Type>* obj_node = obj.Head->next;
		while (obj_node != obj.Head)
		{
			push_back(obj_node->val);
			obj_node = obj_node->next;
		}
	}
	//deconstructor
	template<typename Type>
	list<Type>::~list()
	{
		clear();//清空链表
		delete Head;//释放头结点内存
	}
	//add
	template<typename Type>
	void list<Type>::insert(iterator pos,const Type &value)
	{
		
		DNode<Type>* next_node = pos.ptr;
		
		DNode<Type>* new_node 
			= new DNode<Type>(value,next_node->prior,next_node);//malloc
		
		next_node->prior->next = new_node;
		next_node->prior = new_node;
		length++;
	}
	

	//delete
	//清空链表
	template<typename Type>
	void list<Type>::clear()
	{
		if (!empty())
			list::listfreememory(Head->next, Head->prior);//释放除头结点外的所有节点
		length = 0;//维护length
	}
	//删除节点
	template<typename Type>
	void list<Type>::erase(iterator pos)
	{
		assert(pos != end());
		DNode<Type>* node = pos.ptr;
		node->prior->next = node->next;
		node->next->prior = node->prior;
		delete node;
		length--;
	}
	//algoritm
	//翻转链表
	template<typename Type>
	void list<Type>::reverse()
	{
		DNode<Type>* node = Head;
		do
		{
			DNode<Type>* tmp = node->next;
			node->next = node->prior;
			node->prior = tmp;
			node = node->prior;
		} while (node != Head);
	}


	//operator over load
	
	template<typename Type>
	list<Type>& list<Type>::operator=(const list<Type>& rhs)
	{
		if (this == &rhs)return *this;//自赋值处理
		clear();//清空链表
		for (auto it = rhs.begin(); it != rhs.end(); ++it)
			push_back(it.ptr->val);
		return *this;
	}
	//assert
	template<typename Type>
	void list<Type>::check()const
	{
		assert(Head != nullptr);
		assert(Head->next != nullptr);
		assert(Head->prior != nullptr);
		if (length == 0)
		{
			assert(Head->next == Head);
			assert(Head->prior == Head);
			
		}
		else
		{
			size_t n = 0;
			for (DNode<Type> *p = Head->next; p != Head; p=p->next)
			{
				assert(p != nullptr);
				assert(p->next->prior == p);//保证后面完整
				assert(p->prior->next == p);//保证前面完整
				n++;
				assert(n <= length);
			}
			assert(n == length);
			n = 0;
			for (DNode<Type>* p = Head->prior; p != Head; p = p->prior)
			{
				assert(p != nullptr);
				n++;
				assert(n <= length);
			}
			assert(n == length);

		}
	}
	//static
	template<typename Type>
	void list<Type>::listfreememory(DNode<Type>* start,DNode<Type>* end)
	{
		assert(start != nullptr && end != nullptr);
		start->prior->next = end->next;
		end->next->prior = start->prior;
		while (start != end)
		{
			DNode<Type>* next = start->next;
			//std::cout << start << " DNode\t" << start->val << "\thas been free\n";
			delete start;
			start = next;
		}
		//std::cout << start << " DNode\t" << start->val << "\thas been free\n";
		delete start;
	}
	
};