/*
*已经实现的类型:
*	二叉树BT
*	线索二叉树ThreadBinaryTree
*目标实现的类型
*	带权二叉树WPL
*	二叉排序树BST
*	平衡二叉树AVL
*	红黑树RBT
*--------------------------------------------------------------------*/


#pragma once
#include"String.h"
#include"mystack.h"
#include"myqueue.h"
namespace DSL
{
	template<typename T>class BTree;
	template<typename T>class ThreadTree;
	template<typename T>class BNode;
	template<typename T>class ThreadNode;
	/*--------------------------------------------------------------------
	*
	*  一.函数
	*
	*---------------------------------------------------------------------*/
	//模版函数
	template<typename N>void delete_tree(N* root)
	{
		if (root == nullptr)
			return;
		DSL::queue<N*>Q;
		Q.push(root);
		while (!Q.empty())
		{
			N* p = Q.front();
			Q.pop();
			if (p->left())
				Q.push(p->left());
			if (p->right())
				Q.push(p->right());
			delete p;
		}
	}

	template<typename T>void delete_thread_tree(ThreadNode<T>* root)
	{
		if (root == nullptr)
			return;
		queue<ThreadNode<T>*>Q;
		Q.push(root);
		while (!Q.empty())
		{
			ThreadNode<T>* p = Q.front();
			Q.pop();
			if (p->left() && p->get_ltag() == false)//有左孩子并且不是线索
				Q.push(p->left());
			if (p->right() && p->get_rtag() == false)//有右孩子并且不是线索
				Q.push(p->right());
			delete p;
		}
	}

	template<typename T, typename N>bool Insert(const T& value, N*& root, const std::string& op = "")
	{
		N* pre = nullptr;
		N* p = root;
		N* pre_create_tree = nullptr;
		N* create_tree = nullptr;
		bool create_dir_l = true;//第一次创建新节点的方向是否为左
		if (root == nullptr)//树本来就是空
			p = create_tree = root = new N();

		for (auto it = op.begin(); it != op.end(); ++it)
		{
			if (*it == 'l' || *it == 'L')
			{
				pre = p;
				p = p->lchild;
				if (p == nullptr)
				{
					p = new N();
					pre->lchild = p;//链接新节点
					if (create_tree == nullptr)//如果还没有创造过树
					{
						pre_create_tree = pre;
						create_tree = p;
						create_dir_l = true;
					}
				}
			}
			else if (*it == 'r' || *it == 'R')
			{
				pre = p;
				p = p->rchild;
				if (p == nullptr)
				{
					p = new N();
					pre->rchild = p;//链接新节点
					if (create_tree == nullptr)//如果还没有创造过树
					{
						pre_create_tree = pre;
						create_tree = p;
						create_dir_l = false;
					}
				}
			}
			else//回滚
			{
				delete_tree<N>(create_tree);//删除被创造的树
				if (pre_create_tree)
				{
					if (create_dir_l)
						pre_create_tree->lchild = nullptr;
					else
						pre_create_tree->rchild = nullptr;
				}
				return false;
			}
		}
		p->val = value;
		return true;
	}


	//中序下的迭代器移动
	template<typename T>ThreadNode<T>* getfirstnode(ThreadNode<T>* root)
	{
		if (root == nullptr)return nullptr;
		ThreadNode<T>* ret = root;
		while (ret->get_ltag() == false && ret->left())
			ret = ret->left();
		return ret;
	}
	template<typename T>ThreadNode<T>* getlastnode(ThreadNode<T>* root)
	{
		if (root == nullptr)return nullptr;
		ThreadNode<T>* ret = root;
		while (ret->get_rtag() == false && ret->right())
			ret = ret->right();
		return ret;
	}
	template<typename T>ThreadNode<T>* getnextnode(ThreadNode<T>* node) { return node->get_rtag() ? node->right() : getfirstnode(node->right()); }
	template<typename T>ThreadNode<T>* getprenode(ThreadNode<T>* node) { return node->get_ltag() ? node->left() : getlastnode(node->left()); }
/*--------------------------------------------------------------------
*
* 二.节点类型
*
*---------------------------------------------------------------------*/
	//BNode
	template<typename T>class BNode
	{
		T		val;			//value
		BNode* lchild;			//左孩子指针
		BNode* rchild;			//右孩子指针
		friend class BTree<T>;//为二叉树提供访问私有/保护成员的权限
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
		BNode(const T& val = T{}) :val(val), lchild(nullptr), rchild(nullptr) {}//构造
		BNode<T>* left()const { return lchild; }
		BNode<T>* right()const { return rchild; }
		template<typename T, typename N>friend bool Insert(const T& value, N*& root, const std::string& op);//给插入函数提供访问私有成员的权限

	};
	//ThreadNode
	template<typename T>class ThreadNode
	{
		T val;
		bool ltag;
		bool rtag;
		ThreadNode* lchild;
		ThreadNode* rchild;
		template<typename T, typename N>friend bool Insert(const T& value, N*& root, const std::string& op);//给插入函数提供访问私有成员的权限
		friend class ThreadTree<T>;//给ThreadTree提供访问私有成员的权限
	public:
		ThreadNode() :val(T()), ltag(false), rtag(false), lchild(nullptr), rchild(nullptr) {}
		ThreadNode(const ThreadNode& rhs) = delete;				//删除拷贝构造
		ThreadNode& operator=(const ThreadNode& rhs) = delete;	//删除赋值构造
		ThreadNode<T>* left() const { return lchild; }
		ThreadNode<T>* right()const { return rchild; }
		bool get_ltag() const { return ltag; }
		bool get_rtag() const { return rtag; }

	};
/*--------------------------------------------------------------------
*
* 三.二叉树类型
*
*---------------------------------------------------------------------*/
	//BTree二叉树
	template<typename T>class BTree
	{
		BNode<T>* root;
	public:
		BTree() :root(nullptr) {}
		BTree(const BTree& obj)=delete;					//禁用拷贝构造
		BTree operator=(const BTree& rhs) = delete;		//禁用拷贝赋值
		~BTree() { delete_tree<BNode<T>>(root); }		//析构


		void PreOrder()const;			//先序便利
		void InOrder()const;			//中序遍历
		void PostOrder()const;			//后序遍历
		void LevelOrder()const;			//层次遍历

		void insert(const T& value,const std::string& op="") { Insert<T, BNode<T>>(value, root, op); }
		
	};
	//ThreadTree线索二叉树
	template<typename T>class ThreadTree
	{
		ThreadNode<T>* root;
	public:
		class iterator
		{
			ThreadNode<T>* ptr;
		public:
			iterator(ThreadNode<T>* p) :ptr(p) {}
			T& operator*() { return ptr->val; }//*it
			iterator& operator++() { ptr = getnextnode(ptr); return *this; }//++it
			iterator operator++(int) { iterator old(*this); ptr = getnextnode(ptr); return old; }//it++
			iterator& operator--() { ptr = getprenode(ptr); return *this; }//--it
			iterator operator--(int) { iterator old(*this); ptr = getprenode(ptr); return old; }//it--
			bool operator==(const iterator& rhs) { return ptr == rhs.ptr; }
			bool operator!=(const iterator& rhs) { return !(*this == rhs); }
		};
		ThreadTree() :root(nullptr) {}
		ThreadTree(const ThreadTree& rhs) = delete;//禁用拷贝构造
		ThreadTree& operator=(const ThreadTree& rhs) = delete;//禁用赋值构造
		~ThreadTree() { delete_thread_tree<T>(root); }
		void InThread();//中序线索化
		iterator begin() { return iterator(getfirstnode(root)); }
		iterator end() { return iterator(nullptr); }
		iterator last() { return iterator(getlastnode(root)); }
		void insert(const T& value, const std::string& op = "") { Insert<T, ThreadNode<T>>(value, root, op); }
	};
	

};
#include"Tree.inl"
void btree_insert_test()
{
	DSL::BTree<char>T;
	T.insert('A');
	T.insert('B', "L");
	T.insert('C', "R");
	T.insert('D', "LL");
	T.insert('E', "LR");
	T.InOrder();
}

void thread_tree_insert_test()
{
	DSL::ThreadTree<char>T;
	T.insert('A');
	T.insert('B', "L");
	T.insert('C', "R");
	T.insert('D', "LL");
	T.insert('E', "LR");
	T.insert('F', "RR");
	T.InThread();
	for (auto it = T.last(); it != T.end(); --it)
		std::cout << *it << " ";
}


