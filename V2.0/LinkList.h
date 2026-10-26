#pragma once
#include"Define.h"
//-----------------------------------------------------------------//
/*
*			DataStruct-------LinkList.h
*												time:2026.6.3									
*												created by HFLY
*				
*/
//-----------------------------------------------------------------//
namespace DSL
{
	//·ºÐÍµ¥Á´±í
	template<typename type>
	class GenericLNode
	{

	public:
		GenericLNode();
		GenericLNode(type e);


		virtual bool			HeadInsert(type e);
		virtual bool			TailInsert(type e);
		virtual GenericLNode*	CreateNode(type e);



		type			val;
		GenericLNode*	next;
	};

	//·ºÐÍË«Á´±í
	template<typename type>
	class GenericDNode :public GenericLNode<type>
	{
	public:
		GenericDNode();
		GenericDNode(type e);



		bool			HeadInsert(type e)override;
		bool			TailInsert(type e)override;
		GenericDNode*	CreateNode(type e)override;
		GenericDNode*	prior;
	};
}
#include"GenericLinkList.inl"
