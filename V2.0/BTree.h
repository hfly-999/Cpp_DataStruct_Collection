#pragma once

#include"Stack.h"
#include"Queue.h"
#include"Sort.h"
#include"LinkList.h"
namespace DSL
{
	class BNode;
	class HNode;
	typedef BNode* BTree;
	typedef HNode* HuffmanTree;
	class BNode
	{
	public:
							BNode();
							BNode(ElemType e);

		virtual				~BNode();


							//递归下先根遍历
		virtual void		PreOrder	();


							//非递归下先根遍历
		void				_PreOrder	();


							//递归下中根遍历
		virtual void		InOrder		();


							//非递归下中根遍历
		void				_InOrder	();


							//递归下后根遍历
		virtual void		PostOrder	();


							//非递归下后根遍历
		void				_PostOrder	();


							//层次遍历
		void				LeverOrder	();


							//访问当前节点的元素
		virtual void		visit		();


							//判断当前节点是否为叶子节点
		bool				IsLeaves	();


							//递归法得到当前节点的高度
		unsigned int		GetHight	();


							//比较器
		static int			cmp			(BNode* x, BNode* y);


							//创建节点的虚函数
		virtual BNode*		CreateNode	(ElemType e);//


							//当前节点的值
		ElemType			Data;


							//左孩子指针
		BNode *				lchild;


							//右孩子指针
		BNode *				rchild;	
	};

	//线索二叉树
	class ThreadNode :public BNode
	{
	public:
		ThreadNode();


		
		//左右孩子是否是线索，0表示不是线索，1表示是线索
		int ltag;
		int rtag;
	};
	class HNode :public BNode
	{
	public:
		HNode();
		HNode(int weight);
		


							//用于比较HNode大小的比较比较器
		static int			cmp					(HNode* x, HNode* y);
						


							//哈夫曼树的创建
		static GenericLNode<char>*	CreateHuffmanTree	(HuffmanTree &T,char* str);


							//递归下中根访问树
		void				InOrder				(GenericLNode<char>* HashList);

		void				InOrder()			override;
							//访问
		void				visit				()override;
		
		
		//权值
		int weight;

	};


	//统计字符个数，并且返回一个整形数组
	int* CountChar(char* str);
};