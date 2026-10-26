/*											//
*		DataStruct-Seach					//
*											//
*		Created by HFLY						//
*											//
*				---time:2026.5.22			//
*											//
*/											//

#pragma once
#include"BTree.h"
#include"Sort.h"
namespace DSL
{
	class BSTNode;
	class BBTNode;
	class BSTNode :public BNode//二叉排序树
	{
	public:
		//无参构造函数，默认值域=0X7FFF FFFF
		BSTNode();
		//有参构造函数，允许赋值，值域为e
		BSTNode(ElemType e);
		//析构函数
		~BSTNode() override;
		//------------------------------------------------//
		//二叉排序树的插入算法，虚函数
		virtual BNode* Insert(ElemType e);
		//重写BNode类型的创造节点函数
		BSTNode* CreateNode(ElemType e) override;
		//查找
		BSTNode* Search(ElemType e);

		//------------------------------------------------//
	};
	typedef BSTNode* BSTree;

	class BBTNode :public BSTNode//（Balanced Binary Tree）平衡二叉树节点
	{
	public:
		//无参构造函数，默认值域=0X7FFF FFFF
		BBTNode();
		//有参构造函数，允许赋值，值域为e
		BBTNode(ElemType e);
		//析构函数
		~BBTNode()override;
		//------------------------------------------------//
		//重写BST二叉排序树的插入算法
		BNode*		Insert		(ElemType e) override;
		BBTNode*	CreateNode	(ElemType e) override;
		void		CountBF		();
		//void LLRevolve(BBTNode* T, BBTNode* A, BBTNode* B, BBTNode* C);
		//void LRRevolve(BBTNode* T, BBTNode* A, BBTNode* B, BBTNode* C);
		//void LRRevolve(BBTNode* T, BBTNode* A, BBTNode* B, BBTNode* C);
		//void LRRevolve(BBTNode* T, BBTNode* A, BBTNode* B, BBTNode* C);
		//------------------------------------------------//
	private:
		//高度
		int hight;
		//平衡因子
		int BF;
	};
	typedef BBTNode* BBTree;//平衡二叉树指针
	typedef BBTNode* AVL;
	class RBTNode :public BBTNode
	{
	public:
		//构造与析构函数
		RBTNode(ElemType e);
		~RBTNode();
		//------------------------------------------------//
		//成员函数
		RBTNode* CreateNode(ElemType e);

		//------------------------------------------------//
	private:
		//成员变量
		RBTNode* parent;
		unsigned int color;//0为黑色，1为红色

	};
	typedef RBTNode* RBTree;


	



}
