/*											//
*	DataStruct-GenericLinkList(泛型链表)		//
*											//
*		Created by HFLY						//
*											//
*				---time:2026.6.1			//
*											//
*/											//
#include"LinkList.h"
namespace DSL
{
	template<typename type>
	GenericLNode<type>::GenericLNode()
	{
		//printf("构造了LNode类型\n");
		this->val = (type)0x0000000;
		this->next = nullptr;
	}

	template<typename type>
	GenericLNode<type>::GenericLNode(type e) :GenericLNode()
	{
		this->val = e;
	}

	template<typename type>
	bool GenericLNode<type>::HeadInsert(type e)
	{
		GenericLNode* NewNode = CreateNode(e);
		if (NewNode == nullptr)return false;
		NewNode->next = this->next;
		this->next = NewNode;
		return  true;
	}

	template<typename type>
	bool GenericLNode<type>::TailInsert(type e)
	{
		GenericLNode* p = this;
		while (p->next)p = p->next;
		return p->HeadInsert(e);//对尾节点进行头插
	}

	template<typename type>
	GenericLNode<type>* GenericLNode<type>::CreateNode(type e)
	{
		return new GenericLNode(e);
	}



	//-------------------------------------------------------------------------//
	/*
	*		GenericDoubleLinkList
	*														2026.6.3
	*
	*/
	//-------------------------------------------------------------------------//


	template<typename type>
	GenericDNode<type>::GenericDNode()
	{
		//printf("构造了DNode类型\n");
		this->prior = nullptr;
	}


	template<typename type>
	GenericDNode<type>::GenericDNode(type e) :GenericLNode<type>(e)
	{
		//printf("构造了DNode类型\n");
		this->prior = nullptr;
	}


	template<typename type>
	bool GenericDNode<type>::HeadInsert(type e)
	{
		bool ret = GenericLNode<type>::HeadInsert(e);
		if (ret == false)return ret;
		GenericDNode* NewNode = (GenericDNode*)this->next;
		if (NewNode->next)
		{
			((GenericDNode*)NewNode->next)->prior = NewNode;
		}
		NewNode->prior = this;
		return ret;
	}


	template<typename type>
	bool GenericDNode<type>::TailInsert(type e)
	{
		bool ret = GenericLNode<type>::TailInsert(e);
		if (ret == false)return ret;
		((GenericDNode*)this->next)->prior = this;
		return ret;
	}


	template<typename type>
	GenericDNode<type>* GenericDNode<type>::CreateNode(type e)
	{
		return new GenericDNode(e);
	}
}
