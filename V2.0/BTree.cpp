#include"BTree.h"



//---------------------------BTree.cpp-------------------------------//
/*
*		BNode.cpp
*
*/
namespace DSL
{

	BNode::BNode()
	{
		//printf("构造了BNode类型\n");
		Data = DEFAULT_MAX_SHORT;
		lchild = rchild = nullptr;
	}


	BNode::BNode(ElemType e) :BNode()
	{
		//printf("构造了BNode类型,值为%c\n", e);
		Data = e;
	}


	BNode::~BNode()
	{

		cout << "执行了BNode节点：";
		visit();
		cout << "的析构函数" << endl;
		if (lchild)
			delete lchild;
		if (rchild)
			delete rchild;
		lchild = rchild = nullptr;
	}


	bool BNode::IsLeaves()
	{
		if (
			lchild == nullptr
			&&
			rchild == nullptr
			)
			return true;
		return false;
	}


	void BNode::visit()
	{
		printf("%c ", Data);//默认打印字符
	}


	unsigned int BNode::GetHight()
	{
		if (IsLeaves() == true)
			return 0;
		else if (lchild == nullptr)
			return rchild->GetHight() + 1;
		else if (rchild == nullptr)
			return lchild->GetHight() + 1;
		else
		{
			unsigned int lhight = lchild->GetHight();
			unsigned int rhight = rchild->GetHight();
			return (lhight > rhight ? lhight : rhight) + 1;
		}

	}


	int		BNode::cmp(BNode* x, BNode* y)
	{
		return x->Data - y->Data;
	}


	void BNode::PreOrder()
	{

		visit();
		if (lchild != nullptr)
			lchild->PreOrder();
		if (rchild != nullptr)
			rchild->PreOrder();

	}


	void BNode::_PreOrder()
	{
		GenericStack<BNode*> S;
		S.Push(this);
		BNode* p = nullptr;
		while (S.IsEmpty() == false)
		{
			S.Pop(p);
			p->visit();
			if (p->rchild)
				S.Push(p->rchild);
			if (p->lchild)
				S.Push(p->lchild);
		}
	}


	void BNode::InOrder()
	{
		if (lchild != nullptr)
			lchild->InOrder();
		visit();
		if (rchild != nullptr)
			rchild->InOrder();

	}


	void BNode::_InOrder()
	{
		GenericStack<BNode*> S;
		S.Push(this);
		int status = 0;//0表示压栈操作，1表示出栈操作
		while (S.IsEmpty() == false)
		{
			if (((BNode*)S.GetTop())->lchild && status == 0)
			{
				S.Push(((BNode*)S.GetTop())->lchild);
			}
			else
			{
				BTree p = NULL;
				S.Pop(p);
				p->visit();
				status = 1;//出栈状态
				if (p->rchild)
				{
					S.Push(p->rchild);
					status = 0;//重新进入入栈状态
				}
			}
		}
	}


	void BNode::PostOrder()
	{
		if (lchild != nullptr)
			lchild->PostOrder();
		if (rchild != nullptr)
			rchild->PostOrder();
		visit();
	}


	void BNode::_PostOrder()
	{
		GenericStack<BNode*> S;
		S.Push(this);
		int status = 0;//状态机 0 为入栈，1为出栈
		BNode* pre = nullptr;
		while (S.IsEmpty() == false)
		{
			BNode* top = S.GetTop();
			if (top->lchild && status == 0)
			{
				S.Push(top->lchild);
			}
			else if (top->rchild && top->rchild != pre)
			{
				S.Push(top->rchild);
				status = 0;
			}
			else
			{
				S.Pop(pre);
				status = 1;//出栈
				pre->visit();

			}
		}
	}


	void BNode::LeverOrder()
	{
		GenericQueue<BNode*> Q;
		Q.EnQueue(this);
		BNode* p = NULL;
		while (Q.IsEmpty() == false)
		{
			Q.DeQueue(p);
			if (p == nullptr)continue;
			p->visit();
			if (p->lchild)
				Q.EnQueue(p->lchild);
			if (p->rchild)
				Q.EnQueue(p->rchild);
		}
		delete p;
	}


	BNode* BNode::CreateNode(ElemType e)
	{
		return new BNode(e);
	}


	//---------------------------BTree.cpp-------------------------------//
	/*
	*		ThreadNode.cpp
	*
	*/
	ThreadNode::ThreadNode()
	{
		this->ltag = this->rtag = 0;
	}
	//---------------------------BTree.cpp-------------------------------//
	/*
	*		HNode.cpp
	*
	*/


	HNode::HNode()
	{
		this->weight = 0;

	}


	HNode::HNode(int weight)
	{
		this->weight = weight;
	}


	int	HNode::cmp(HNode* x, HNode* y)
	{
		return x->weight - y->weight;
	}


	GenericLNode<char>* HNode::CreateHuffmanTree(HuffmanTree& T, char* str)
	{
		GenericLNode<char>* ret = new GenericLNode<char>[127];//申请哈希表内存
		int* hash = CountChar(str);//统计字符的哈希表
		GenericHeap<HNode*>Heap = GenericHeap<HNode*>(cmp, Small);//HNode节点的小顶堆
		for (int i = 1; i < 127; i++)
		{
			if (hash[i] == 0)continue;
			HNode* NewNode = new HNode(hash[i]);
			NewNode->Data = i;
			Heap.Push(NewNode);
		}
		while (Heap.GetLength() != 1)
		{
			//选用两小造新树
			HNode* son1 = Heap.Pop();//出堆
			HNode* son2 = Heap.Pop();//出堆
			HNode* father = new HNode(son1->weight + son2->weight);//建立新节点
			father->lchild = son1;
			father->rchild = son2;
			//新树入堆
			Heap.Push(father);//新节点入堆
		}
		T = Heap.Pop();//构建好了哈夫曼树
		T->InOrder(ret);
		return ret;//返回构建好的哈希表
	}


	void HNode::visit()
	{
		if (this->Data == DEFAULT_MAX_SHORT)return;
		else printf("节点：%c权值%d ", this->Data, this->weight);
	}
	void HNode::InOrder(GenericLNode<char>* HashList)
	{
		static GenericStack<int>S;
		int x;
		if (lchild)
		{

			S.Push(0);
			((HNode*)lchild)->InOrder(HashList);
			S.Pop(x);
		}
		if (IsLeaves() == true)//为叶子节点
		{
			for (unsigned int i = 0; i < S.top; i++)
			{
				HashList[this->Data].TailInsert('0' + S.Data[i]);
			}
		}
		if (rchild)
		{
			S.Push(1);
			((HNode*)rchild)->InOrder(HashList);
			S.Pop(x);
		}
	}

	void HNode::InOrder()
	{
		static GenericStack<int>S;
		int x;
		if (lchild)
		{

			S.Push(0);
			lchild->InOrder();
			S.Pop(x);
		}
		visit();
		if (IsLeaves() == true)
		{
			printf("哈夫曼编码为：");
			for (unsigned int i = 0; i < S.top; i++)
			{
				printf("%d ", S.Data[i]);
			}

			printf("\n");


		}
		if (rchild)
		{
			S.Push(1);
			rchild->InOrder();
			S.Pop(x);
		}
	}


	int* CountChar(char* str)
	{
		int* ret = (int*)malloc(127 * sizeof(int));
		if (ret == NULL)return ret;
		for (int i = 0; i < 127; i++)
			ret[i] = 0;
		while (*str)
		{
			ret[*str++]++;
		}
		return ret;
	}
}