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
#include<queue>
namespace DSL
{
	template<typename T>class BTree;
	template<typename T>class ThreadTree;
	template<typename T>class BNode;
	template<typename T>class ThreadNode;
	class HNode;
	class HuffmanTree;
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

		for (auto it = op.begin(); it != op.end(); ++it)//遍历op
		{
			if (*it == 'l' || *it == 'L')
			{
				pre = p;//记录父节点
				p = p->lchild;//往左走
				if (p == nullptr)//走到了空节点
				{
					p = new N();//新建节点
					pre->lchild = p;//链接新节点
					if (create_tree == nullptr)//从来没有新建立过节点
					{
						create_tree = p;
						pre_create_tree = pre;
						create_dir_l = true;
					}
				}
			}
			else if (*it == 'r' || *it == 'R')
			{
				pre = p;//记录父节点
				p = p->rchild;//往右走
				if (p == nullptr)
				{
					p = new N();//建立新节点
					pre->rchild = p;//链接新节点
					if (create_tree == nullptr)//从来没有新建立过节点
					{
						create_tree = p;//记录新节点
						pre_create_tree = pre;//记录新节点的父节点
						create_dir_l = false;//记录方向
					}
				}
			}
			else//回滚
			{
				if (pre_create_tree)//新树有父节点
					create_dir_l ? pre_create_tree->lchild = nullptr : pre_create_tree->rchild = nullptr;
				else if (create_tree)//有创建过树,但是创建的树没有父节点
					root = nullptr;
				delete_tree<N>(create_tree);
				return false;//提前返回
			}
		}
		p->val = value;
		return true;
	}

	template<typename T>void DeInthread(ThreadNode<T>* root)//去线索化
	{
		if (root == nullptr)return;
		DeInthread(root->left());
		if (root->get_ltag() == true)
		{
			root->ltag = false;
			root->lchild = nullptr;
		}
		if (root->get_rtag() == true)
		{
			root->rtag = false;
			root->rchild = nullptr;
		}
		DeInthread(root->right());
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
		while (ret->get_rtag()==false&&ret->right())
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
		template<typename T>friend void DeInthread(ThreadNode* root);
		friend class ThreadTree<T>;//给ThreadTree提供访问私有成员的权限
	public:
		ThreadNode() :val(T()), ltag(false), rtag(false), lchild(nullptr), rchild(nullptr) {}
		ThreadNode(const ThreadNode& rhs) = delete;				//删除拷贝构造
		ThreadNode& operator=(const ThreadNode& rhs) = delete;	//删除赋值构造
		ThreadNode<T>* left() const { return lchild; }			//获得节点的左孩子,注意,左孩子可能是线索
		ThreadNode<T>* right()const { return rchild; }			//获得节点的右孩子,注意,右孩子可能是线索
		bool get_ltag() const { return ltag; }
		bool get_rtag() const { return rtag; }

	};
	//huffmantree
	class HNode
	{
		int we;
		char val;
		HNode* lchild;
		HNode* rchild;
		friend class HuffmanTree;
	public:
		HNode(int we = 0, char value = '\0', HNode* lchild = nullptr, HNode* rchild = nullptr)
				:we(we), val(value), lchild(lchild), rchild(rchild) {}
		HNode(const HNode& rhs) = delete;				//删除拷贝构造
		HNode& operator=(const HNode& rhs) = delete;	//删除拷贝析构
		HNode* left()const { return lchild; }			//获得左孩子指针
		HNode* right()const { return rchild; }			//获得右孩子指针
		int weight()const { return we; }				//获得节点权重
	
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
			T& operator*()const { return ptr->val; }//*it
			iterator& operator++() { ptr = getnextnode(ptr); return *this; }//++it
			iterator operator++(int) { iterator old(*this); ptr = getnextnode(ptr); return old; }//it++
			iterator& operator--() { ptr = getprenode(ptr); return *this; }//--it
			iterator operator--(int) { iterator old(*this); ptr = getprenode(ptr); return old; }//it--
			bool operator==(const iterator& rhs)const { return ptr == rhs.ptr; }
			bool operator!=(const iterator& rhs)const { return !(*this == rhs); }
		};

		class const_iterator
		{
			ThreadNode<T>* ptr;
		public:
			const_iterator(ThreadNode<T>* p) :ptr(p) {}
			const T& operator*()const { return ptr->val; }//*it
			const_iterator& operator++() { ptr = getnextnode(ptr); return *this; }//++it
			const_iterator operator++(int) { const_iterator old(*this); ptr = getnextnode(ptr); return old; }//it++
			const_iterator& operator--() { ptr = getprenode(ptr); return *this; }//--it
			const_iterator operator--(int) { const_iterator old(*this); ptr = getprenode(ptr); return old; }//it--
			bool operator==(const const_iterator& rhs)const { return ptr == rhs.ptr; }
			bool operator!=(const const_iterator& rhs)const { return !(*this == rhs); }
		};

		ThreadTree() :root(nullptr) {}
		ThreadTree(const ThreadTree& rhs) = delete;//禁用拷贝构造
		ThreadTree& operator=(const ThreadTree& rhs) = delete;//禁用赋值构造
		~ThreadTree() { delete_thread_tree<T>(root); }
		void InThread();//中序线索化
		void DeThread() { DeInthread(root); }

		iterator		begin()		{ return iterator(getfirstnode(root)); }
		iterator		end()		{ return iterator(nullptr); }
		iterator		last()		{ return iterator(getlastnode(root)); }

		const_iterator	begin()		const { return const_iterator(getfirstnode(root)); }
		const_iterator	end()		const { return const_iterator(nullptr); }
		const_iterator	last()		const { return const_iterator(getlastnode(root)); }

		void insert(const T& value, const std::string& op = "") { Insert<T, ThreadNode<T>>(value, root, op); }
	};
	//huffmanTree
	class HuffmanTree
	{
		vector<size_t>hash_list;
		vector<String>translate_list;//翻译表
		HNode* root;//哈夫曼树的根节点
	public:
		HuffmanTree(const String& str) :hash_list(),translate_list(), root(nullptr)
		{
			for (auto it = str.begin(); it != str.end(); ++it)
				hash_list[*it]++;//建立哈希表
			std::priority_queue<HNode*>heap;
			for (auto it = hash_list.begin(); it != hash_list.end(); ++it)
				if (*it != 0)
					heap.push(new HNode(*it, it - hash_list.begin()));//所有节点入堆
			while (heap.size() != 1)
			{
				HNode* lt = heap.top();
				heap.pop();
				HNode* rt = heap.top();
				heap.pop();
				heap.push(new HNode(lt->weight() + rt->weight(), '\0', lt, rt));//选用两小造新树
			}
			root = heap.top();
			
		}
	};
/*---------------------------------------------------------------------------------------------------------------
* 
*	四.测试用函数
* 
* 
*---------------------------------------------------------------------------------------------------------------*/

	void btree_insert_test_1()
	{
		BTree<char>T;
		T.insert('A', "==");
		T.insert('B', "==");
		T.insert('C', "==");
		T.insert('D', "==");
		T.insert('E', "==");
		T.InOrder();
	}
	
	void btree_insert_test_2()
	{
		BTree<char>T;
		T.insert('A', "");
		T.insert('B', "L");
		T.insert('C', "R");
		T.insert('D', "LL");
		T.insert('E', "LR");
		T.insert('F', "LLL");
		T.insert('G', "LR*");
		T.insert('G', "L*R");
		T.insert('G', "*LR");
		T.InOrder();
	}

	void btree_insert_test_3()
	{
		BTree<char>T;
		T.insert('A', "LLL");
		T.insert('B', "LLR");
		T.insert('C', "LRL");
		T.insert('D', "LRR");
		T.insert('E', "RLL");
		T.insert('F', "RLR");
		T.insert('G', "RRL");
		T.insert('H', "RRR");
		T.insert('A', "L*L");
		T.insert('B', "*LR");
		T.insert('C', "LR*");
		T.insert('D', "LR*");
		T.insert('E', "R**");
		T.insert('F', "R*R");
		T.insert('G', "*RL");
		T.insert('H', "***");
		T.InOrder();
	}

	void thread_tree_insert_test()
	{
		ThreadTree<char>T;
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


};
#include"Tree.inl"




