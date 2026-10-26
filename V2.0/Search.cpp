#include"Search.h"
namespace DSL
{
//----------------------------Search.h-----------------------------//
/*			class BSTNode *BSTree（二叉排序树）
*
*
*														BSTree.cpp
* 												------Created by HFLY
*/
	BSTNode::BSTNode()
	{
		printf("构造了BSTNode类型\n");
		Data = DEFAULT_MAX_SHORT;
	}


	BSTNode::BSTNode(ElemType e) :BNode(e)
	{
		//printf("构造了BSTNode类型,值为%c\n", e);
	}


	BSTNode::~BSTNode()
	{

		cout << "执行了BSTNode节点：";
		visit();
		cout << "的析构函数" << endl;

	}


	BNode* BSTNode::Insert(ElemType e)
	{
		if (this->Data == DEFAULT_MAX_SHORT)
		{
			this->Data = e;
			return nullptr;
		}

		else
		{
			BTree NewNode = CreateNode(e);
			BTree pre = nullptr;
			BTree p = this;
			int tag = 0;
			while (p)
			{
				if (cmp(NewNode, p) > 0)//如果e比当前节点值域大
				{
					tag = 1;
					pre = p;
					p = p->rchild;
				}
				else//小
				{
					tag = 0;
					pre = p;
					p = p->lchild;
				}
			}


			if (tag)
				pre->rchild = NewNode;
			else pre->lchild = NewNode;
			return pre;
		}

	}


	BSTNode* BSTNode::CreateNode(ElemType e)
	{
		return new BSTNode(e);
	}


	BSTNode* BSTNode::Search(ElemType e)
	{
		BSTNode* p = this;
		while (p)
		{
			if (e > p->Data)
				p = (BSTNode*)p->rchild;
			else if (e < p->Data)
				p = (BSTNode*)p->lchild;
			else return p;
		}
		return p;
	}

//----------------------------Search.h-----------------------------//
/*			class BBTNode *BBTree（Blanced Binar Tree平衡二叉树）
*
*
*														BSTree.cpp
* 												------Created by HFLY
*/
	BBTNode::BBTNode()
	{
		printf("构造了BBTNode类型\n");
		hight = 0;
		BF = 0;//把平衡因子设置为0即可

	}


	BBTNode::BBTNode(ElemType e) :BSTNode(e)//去执行父类的有参构造函数
	{

		printf("构造了BBTNode类型,值为%c\n", e);
		hight = 0;
		BF = 0;//把平衡因子设置为0即可
	}


	BBTNode::~BBTNode()
	{
		cout << "执行了BBTNode节点：";
		visit();
		cout << "的析构函数" << endl;
	}


	BNode* BBTNode::Insert(ElemType e)
	{
		//先调用父类的插入算法
		BBTNode* pre = (BBTNode*)BSTNode::Insert(e);
		//子类的AVL算法
		return pre;
	}


	BBTNode* BBTNode::CreateNode(ElemType e)
	{
		return new BBTNode(e);
	}


	void BBTNode::CountBF()
	{
		if (lchild != nullptr && rchild != nullptr)
		{
			this->BF = this->lchild->GetHight() - this->rchild->GetHight();
			((BBTNode*)lchild)->CountBF();
			((BBTNode*)rchild)->CountBF();
		}
		else if (lchild != nullptr)
		{
			this->BF = this->lchild->GetHight();
			((BBTNode*)lchild)->CountBF();
		}
		else if (rchild != nullptr)
		{
			this->BF -= this->rchild->GetHight();
			((BBTNode*)rchild)->CountBF();
		}
		else
		{
			this->BF = 0;
		}
	}


//----------------------------Search.h-----------------------------//
/*	class RBTNode *RBTree（Red And Black Tree红黑树）
*
*
*														RBTree.cpp
* 												------Created by HFLY
*/

	RBTNode::RBTNode(ElemType e) :BBTNode(e)
	{
		printf("构造了RBTNode类型,值为%c\n", e);
		parent = nullptr;
		color = 0;//颜色默认为黑色
	}


	RBTNode::~RBTNode()
	{
		cout << "执行了RBTNode节点：";
		visit();
		cout << "的析构函数" << endl;
	}


	RBTNode* RBTNode::CreateNode(ElemType e)
	{
		return new RBTNode(e);
	}
}


