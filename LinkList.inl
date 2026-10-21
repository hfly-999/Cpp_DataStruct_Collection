
namespace DSL
{
	//传入链的第一个节点,释放整条链占用的内存
	template<typename type>
	void LinkList<type>::LinkMemoryfree(LNode<type>* node)
	{
		while (node)
		{
			LNode<type>* pre = node;
			node = node->next;
			delete pre;
		}//依次释放链表节点
	}
	template<typename type>
	LinkList<type>::LinkList() :
		Head(new LNode<type>()),
		Tail(Head)
	{
	}
	template<typename type>
	LinkList<type>::LinkList(const LinkList<type>& obj) :
		Head(new LNode<type>()),
		Tail(Head)
	{
		LNode<type>* obj_node = obj.Head->next;
		while (obj_node)
		{
			Tail->next = new LNode<type>(obj_node->value);
			Tail = Tail->next;
			obj_node = obj_node->next;
		}
	}
	template<typename type>
	LinkList<type>::~LinkList()
	{
		LinkMemoryfree(Head);
	}
	template<typename type>
	LinkList<type>& LinkList<type>::operator=(const LinkList<type>& rhs)
	{
		assert(!this == &rhs);
		LinkList<type>::LinkMemoryfree(Head->next);
		Tail = Head;
		LNode<type>* rhs_node = rhs.Head->next;
		while (rhs_node)
		{
			Tail->next = new LNode<type>(rhs_node->value);
			Tail = Tail->next;
			rhs_node = rhs_node->next;
		}
		return *this;
	}

	template<typename type>
	void LinkList<type>::HeadInsert(type element)
	{
		LNode<type>* new_node = new LNode<type>(element);
		if (empty())//链表为空
		{
			Head->next = new_node;
			Tail = new_node;
		}
		else//链表非空
		{
			new_node->next = Head->next;
			Head->next = new_node;
		}
	}
	template<typename type>
	void LinkList<type>::push_back(type element)
	{
		LNode<type>* new_node = new LNode<type>(element);
		if (empty())//链表为空
		{
			Head->next = new_node;
			Tail = new_node;
		}
		else//链表非空
		{
			new_node->next = Tail->next;
			Tail->next = new_node;
			Tail = Tail->next;
		}
	}
	template<typename type>
	bool LinkList<type>::empty()const
	{
		return Head == Tail;//头指针和尾指针指向头结点时候为空
	}
	
}








