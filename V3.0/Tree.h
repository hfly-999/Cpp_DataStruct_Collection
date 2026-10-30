#pragma once


#include"mystack.h"
#include"myqueue.h"
namespace DSL
{
	template<typename T>
	class BTree;
	template<typename T>
	class BNode
	{
		T		val;			//value
		BNode* lchild;			//左孩子指针
		BNode* rchild;			//右孩子指针
		friend class BTree<T>;
		void visit()const
		{
			std::cout << this << " " << this->val << "\n";

			std::cout << "\t" << this->lchild << " ";
			if (lchild)
				std::cout << lchild->val;
			std::cout << "\n";
			std::cout << "\t" << this->rchild << " ";
			if (rchild)
				std::cout << rchild->val;
			std::cout << "\n";
		}
	public:
		BNode(
			T val = T{},
			BNode<T>* lchild = nullptr,
			BNode<T>* rchild = nullptr
		) :
			val(val),
			lchild(lchild),
			rchild(rchild) 
		{}//构造

	};
	/*-----------------------------------Tree.h-----------------------------------*/
	template<typename T>
	class BTree
	{
		BNode<T>* tree;
		static void delete_tree(BNode<T>* tree);
	public:
		BTree() :tree(nullptr) {}
		BTree(const BTree& obj)=delete;	//不要拷贝构造
		BTree operator=(const BTree& rhs) = delete;//不要拷贝赋值
		~BTree();						//析构
		bool Insert(T value, const std::string& op = "");//插入
		void PreOrder()const;			//先序便利
		void InOrder()const;			//中序遍历
		void PostOrder()const;			//后序遍历
		void LevelOrder()const;			//层次遍历
		
	};


};
#include"Tree.inl"
void btree_insert_test()
{
	BTree<char> T;
	T.Insert('A');
	T.Insert('B', "l");
	T.Insert('C', "r");
	T.Insert('D', "ll");
	T.Insert('E', "lr");
	T.Insert('F', "RL");
	T.Insert('G', "RRG");
	T.LevelOrder();
}

