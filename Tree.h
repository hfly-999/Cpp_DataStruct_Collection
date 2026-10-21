//#pragma once
//
//
//#include"Queue.h"
//#include"Stack.h"
//
//namespace DSL
//{
//	template<typename type>
//	class BNode
//	{
//		type	val;			//value
//		BNode* lchild;			//左孩子指针
//		BNode* rchild;			//右孩子指针
//	public:
//		BNode(
//			type value = type{},
//			BNode<type>* lchild=nullptr,
//			BNode<type>* rchild=nullptr
//		);							//有参构造
//		BNode(const BNode& obj);	//拷贝构造函数
//		~BNode();	//无参析构
//		
//		
//		void Setlchild(BNode<type>* lchild);		//设置左子树指针
//		BNode<type>*& leftchild()const;				//设置左子树指针
//		void Setlchildnullptr();					//设置左子树指针为空
//		void Setrchild(BNode<type>* rchild);		//设置右子树指针
//		BNode<type>*& rightchild()const;			//设置右子树指针
//		void Setrchildnullptr();					//设置右子树指针为空
//		void visit()const;
//		void SetValue(type value);					//设置节点value值
//		type& SetValue()const;						//设置节点value值
//		type GetValue()const;						//获取节点value值
//
//		BNode* Getlchild()const;
//		BNode* Getrchild()const;
//
//	};
//	/*-----------------------------------Tree.h-----------------------------------*/
//	template<typename type>
//	class BTree
//	{
//		BNode<type>* T;
//	public:
//		BTree(type value = type{});				//有参构造
//		BTree(BNode<type>* T);			//有参构造
//		BTree(const BTree& obj);		//拷贝构造
//		virtual ~BTree();				//虚析构
//		bool Insert(type value, const std::string op= "");//插入
//		void PreOrder()const;			//先序便利
//		void InOrder()const;			//中序遍历
//		void PostOrder()const;			//后序遍历
//		void LevelOrder()const;			//层次遍历
//	};
//
//#include"Tree.inl"
//};
//
//
//
//void BNodeCopyConstructor();
//
//void PreOrderTest();
//
//void InOrderTest1();
//
//void InOrderTest2();
//
//void PostOrderTest();
//
//void LevelOrderTest();