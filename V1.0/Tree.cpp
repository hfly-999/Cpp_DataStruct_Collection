#include"Tree.h"





bool visit(BiTree Node)//访问节点操作
{
	if (!Node)return false;
	if (sizeof(ElemType)==1)
	{
		printf("%c ", Node->data);
	}
	else if (sizeof(ElemType) == 4)
	{
		printf("%d ", Node->data);
	}
	return true;
}
/*------------------------------Tree.cpp------------------------------*/
//三大遍历的递归算法
/*------------------------------Tree.cpp------------------------------*/
bool Traverse_DLR(BiTree root)  
{
	if (!root)return false;
	
	visit(root);
	if (root->lchild)
		Traverse_DLR(root->lchild);
	if (root->rchild)
		Traverse_DLR(root->rchild);
	return true;
	
}

bool Traverse_LDR(BiTree root)
{
	if (!root)return false;
	if (root->lchild)
		Traverse_LDR(root->lchild);
	visit(root);
	if (root->rchild)
		Traverse_LDR(root->rchild);
	return true;
}

bool Traverse_LRD(BiTree root)
{
	if (!root)return false;

	if (root->lchild)
		Traverse_LRD(root->lchild);
	if (root->rchild)
		Traverse_LRD(root->rchild);
	visit(root);
	return true;

}

/*------------------------------Tree.cpp------------------------------*/

bool Init(BiTree& T)
{
	T = (BiNode*)malloc(sizeof(BiNode));
	if (!T)return false;
	T->lchild = T->rchild = NULL;
	return true;
}

unsigned int Count(BiTree BT)
{
	if (!BT)return 0;
	else
	{
		return 1 + Count(BT->lchild) + Count(BT->rchild);
	}
}

unsigned int CountLeaves(BiTree BT)
{
	if (!BT)return 0;
	else if (BT->lchild == NULL && BT->rchild == NULL)return 1;
	else
	{
		return CountLeaves(BT->lchild) + CountLeaves(BT->rchild);
	}
}



/*-----------------------------------------------------------------------------------------------*/
//线索二叉树
bool Init(ThreadTree& T)
{
	T = (ThreadNode*)malloc(sizeof(ThreadNode));
	if (T)
	{
		T->lchild = T->rchild = NULL;//左右孩子指针置NULL
		T->ltag = T->rtag = 0;//没有线索化
		return true;
	}
	else return false;
}

bool visit(ThreadTree& Node,ThreadTree &pre)
{
	if (!Node)return false;
	if (Node->lchild == NULL)//如果当前节点的没有左孩子，那么指向前驱
	{
		Node->lchild = pre;
		Node->ltag = 1;
	}
	if (pre && pre->rchild == NULL)
	{
		pre->rchild = Node;
		pre->rtag = 1;
	}
	if (pre)
		printf("%c %c \n", pre->data, Node->data);
	else
		printf("%c %c \n", NULL, Node->data);
	pre = Node;
	return true;
}

bool Traverse_DLR(ThreadTree root)
{
	if (!root)return false;
	printf("%c ", root->data);
	Traverse_DLR(root->lchild);

	Traverse_DLR(root->rchild);
	return true;
}

bool InThread_LDR(ThreadTree& root, ThreadTree& pre)
{
	if (!root)return false;
	else
	{
		visit(root,pre);
		if(root->ltag==0)InThread_LDR(root->lchild,pre);
	    if(root->rtag==0)InThread_LDR(root->rchild,pre);
		return true;
	}
}

bool CreateInThread(ThreadTree& T)
{
	if (!T)return false;
	ThreadNode* pre = NULL;//全局变量
	InThread_LDR(T,pre);
	pre->rtag = 1;
	pre->rchild = NULL;
	return true;
}
bool SeqTraverse(ThreadTree root)
{
	if (root == NULL)return false;
	while (root)
	{
		printf("%c ", root->data);//访问当前节点
		if (root->lchild&&root->ltag==0)
		{
			root = root->lchild;
		}
		else
			root = root->rchild;
	}
	return true;
}

/*-----------------------------------------------------------------------------------------------*/
//非递归遍历二叉树

bool LeverOrder(BiTree root)//层次遍历二叉树
{
	if (!root)return false;
	else
	{
		BTQueue Q;
		Init(Q);
		EnQueue(Q, root);
		while (!IsEmpty(Q))
		{
			DeQueue(Q, root);
			visit(root);
			if (root->lchild)
				EnQueue(Q, root->lchild);
			if (root->rchild)
				EnQueue(Q, root->rchild);
		}
	}
	return true;
}






bool Init(BTStack &T)
{
	T.base = T.top = 0;
	return true;
}


/*-----------------------------------------------------------------------------------------------*/
//408
unsigned int GetDepth(BiTree T)
{
	unsigned int left = 0;
	unsigned int right = 0;
	if (T->lchild)
		left = GetDepth(T->lchild);
	else left = 0;
	if (T->rchild)
		right = GetDepth(T->rchild);
	else right = 0;
	return 1 + (left > right ? left : right);
}

unsigned int GetDepth_while(BiTree root)
{
	if (root == NULL)return 0;
	BTQueue Q;
	Init(Q);
	EnQueue(Q, root);
	unsigned int ptr = Q.tail;
	unsigned int ret = 0;
	while (!IsEmpty(Q))
	{
		while (Q.head != ptr)
		{
			DeQueue(Q, root);
			if (root->lchild)EnQueue(Q, root->lchild);
			if (root->rchild)EnQueue(Q, root->rchild);
		}
		ptr = Q.tail;
		ret++;
	}
	
	return ret;
}//非递归法求树深度


bool FoundBinaryTree(BiTree& BT)
{
	char ch;
	ch = getchar();
	if (ch == '\n')return false;
	if (ch == '#')BT = NULL;
	else
	{
		BT = (BiNode*)malloc(sizeof(BiNode));
		Init(BT);
		BT->data = ch;
		FoundBinaryTree(BT->lchild);
		FoundBinaryTree(BT->rchild);
	}
	return true;

}




bool Copy(BiTree& BT, BiTree& NewBT)
{
	if (!BT)
	{
		NewBT = NULL;
		return false;
	}
	else
	{
		Init(NewBT);
		NewBT->data = BT->data;
		Copy(BT->lchild, NewBT->lchild);
		Copy(BT->rchild, NewBT->rchild);
		return true;
	}
}


bool IsCompleteBinaryTree(BiTree T)
{
	BTQueue Q;
	Init(Q);
	EnQueue(Q,T);
	while (!IsEmpty(Q))
	{
		DeQueue(Q, T);
		if(T)
		{
			EnQueue(Q, T->lchild);
			EnQueue(Q, T->rchild);
		}
		else
		{
			while (!IsEmpty(Q))
			{
				DeQueue(Q, T);
				if (T)return false;
			}
		}
	}
	return true;


}

unsigned int Count_n_2(BiTree T)
{
	if (T == NULL)return 0;
	if (T->lchild && T->rchild)return 1 + Count_n_2(T->lchild) + Count_n_2(T->rchild);
	else return Count_n_2(T->lchild) + Count_n_2(T->rchild);
}

void ExchangeLeftAndRight(BiTree T)
{
	if (T == NULL)return;
	BiTree tmp = T->lchild;
	T->lchild = T->rchild;
	T->rchild = tmp;
	ExchangeLeftAndRight(T->lchild);
	ExchangeLeftAndRight(T->rchild);
}

bool IsSimilar(BiTree T1, BiTree T2)
{
	if (T1 == NULL && T2 == NULL)
		return true;
	else if (T1 == NULL || T2 == NULL)return false;
	else return IsSimilar(T1->lchild, T2->lchild) && IsSimilar(T1->rchild, T2->rchild);
}

void DeleteXTree(BiTree T)//递归法删除树
{
	if (T == NULL)return;
	else
	{
		DeleteXTree(T->lchild);
		DeleteXTree(T->rchild);
		free(T);
		T = NULL;
	}
}

void DelXInTheTree(BiTree T, ElemType x)
{
	if (T->data == x)
		DeleteXTree(T);
	if (!T)return;
	BTQueue Q;
	Init(Q);
	EnQueue(Q, T);
	while (!IsEmpty(Q))
	{
		DeQueue(Q, T);
		if (T->lchild->data == x)//如果左孩子值为x
		{
			DeleteXTree(T->lchild);
			T->lchild = NULL;
		}
		else
		{
			if (T->lchild)
				EnQueue(Q, T->lchild);
		}
		
		if (T->rchild->data == x)
		{
			DeleteXTree(T->rchild);
			T->rchild = NULL;
		}
		
		else
		{
			if (T->rchild)
				EnQueue(Q, T->rchild);
		}
			
	}
}
BTStack S;
void testFindXAncestor(BiTree T, ElemType x)
{
	
	Init(S);
	FindXAncestor(T, x);

}

void FindXAncestor(BiTree T,ElemType x)
{
	
	if (T == NULL)return;
	Push(S, T);
	FindXAncestor(T->lchild,x);
	FindXAncestor(T->rchild,x);
	if (T->data == x)
		for (int i = 0; i < S.top - 1; i++)
			printf("%c ", S.arr[i]->data);
	Pop(S, T);
}
BTStack Sp, Sq;

void FindMostCloseSameAncestor(BiTree root, BiTree p, BiTree q, BiTree& r)
{
	Init(Sp);
	Init(Sq);
	Init(S);
	Reverse_LRD(root, p, q, r);
	while (Sp.arr[Sp.base] == Sq.arr[Sq.base])
	{
		Sp.base++;
		Sq.base++;
	}
	r = Sp.arr[Sp.base-1];

}

void Reverse_LRD(BiTree root, BiTree p, BiTree q, BiTree& r)
{
	if (root == NULL)return;
	Push(S,root);
	Reverse_LRD(root->lchild, p, q, r);
	Reverse_LRD(root->rchild, p, q, r);
	int i;

	if (root == p)
		for (i = 0; i < S.top; i++)
		{
			Sp.arr[i] = S.arr[i];
			Sp.top++;
		}

	if (root == q)
		for (i = 0; i < S.top; i++)
		{
			Sq.arr[i] = S.arr[i];
			Sq.top++;
		}
		
	Pop(S, root);
}


void LinkLeavesNode(BiTree T, LinkList head)
{
	if (T == NULL)return;
	if (T->lchild == NULL && T->rchild == NULL)
	{
		LinkList ptr = head;
		while (ptr->next)ptr = ptr->next;
		LinkList NewNode;
		Init(NewNode);
		NewNode->data = T->data;
		ptr->next = NewNode;
		NewNode->next = NULL;
	}
	LinkLeavesNode(T->lchild, head);
	LinkLeavesNode(T->rchild, head);

}

unsigned int CalWPL(BiTree T)
{
	unsigned int ret = 0;
	BTStack S;
	Init(S);
	CalWPL_Traverse_LRD(T, S, ret);
	return ret;
}

void CalWPL_Traverse_LRD(BiTree T, BTStack S, unsigned int &ret)
{
	if (T == NULL)return;
	Push(S, T);
	CalWPL_Traverse_LRD(T->lchild, S, ret);
	CalWPL_Traverse_LRD(T->rchild, S, ret);


	//visit
	if (T->lchild == NULL && T->rchild == NULL)
	{
		int i;
		for (i = 0; i < S.top; i++)
			ret += S.arr[i]->data;
	}
	Pop(S, T);
	//visit
}

void PreTransPost(ElemType *pre, ElemType *post)
{
	unsigned int Length = 0;
	while (pre[Length])Length++;
	PreTransPost_shift(pre, 0, Length);
	unsigned int i = 0;
	for (i; i < Length; i++)
		post[i] = pre[i];	
}

void PreTransPost_shift(ElemType pre[], unsigned int left, unsigned right)//DLR->LRD
{
	ElemType tmp = pre[left];
	unsigned int i;
	for (i = left + 1; i < right; i++)
	{
		pre[i - 1] = pre[i];
	}
	pre[i - 1]=tmp;
	if (right - left > 2)
	{
		PreTransPost_shift(pre, left, (left + right) / 2);
		PreTransPost_shift(pre, (left + right) / 2, right - 1);
	}
}


void TranslateBiTreeToLDRExpress(BiTree T,BiTree root)
{
	if (T == NULL)return;
	if (GetDepth(T) > 1 && T != root)
	{
		printf("(");
	}
	TranslateBiTreeToLDRExpress(T->lchild,root);
	printf("%c", T->data);
	TranslateBiTreeToLDRExpress(T->rchild,root);
	if (GetDepth(T) > 1 && T != root)
	{
		printf(")");
	}
}

void BiTreeTranslateToLDRExpree(BiTree T, unsigned int depth)
{
	if (T == NULL)return;
	else if (T->lchild == NULL && T->rchild == NULL)
	{
		printf("%c", T->data);
	}//叶子结点处理
	else
	{
		if (depth > 1)
			printf("(");
		BiTreeTranslateToLDRExpree(T->lchild, depth + 1);
		printf("%c", T->data);
		BiTreeTranslateToLDRExpree(T->rchild, depth + 1);
		if (depth > 1)
			printf(")");
	}
}

/*-----------------------------------------------------------------------------------------------*/
//树和森林


BiTree CreateHuffmanTree(const char* ch, const int* arr)
{
	unsigned int length = 0,i=0;
	while (ch[length])length++;
	if (length == 0)return NULL;
	BiTree* HuffmanTree = (BiTree*)malloc(length*sizeof(BiTree));
	if (!HuffmanTree)return NULL;
	for (i = 0; i < length; i++)
	{
		Init(HuffmanTree[i]);
		HuffmanTree[i]->data = ch[i];
		HuffmanTree[i]->weight = arr[i];
	}
	SortHuffmanTree(HuffmanTree, length);
	while (length != 1)
	{
		BiTree NewNode;
		Init(NewNode);
		NewNode->weight = HuffmanTree[0]->weight + HuffmanTree[1]->weight;
		NewNode->lchild = HuffmanTree[0];
		NewNode->rchild = HuffmanTree[1];
		HuffmanTree[0] = NewNode;
		for (i = 1; i < length-1; i++)
		{
			HuffmanTree[i] = HuffmanTree[i + 1];
		}
		length--;
		SortHuffmanTree(HuffmanTree, length);
	}
		
	return HuffmanTree[0];
}


void SortHuffmanTree(BiTree* HuffmanTree,unsigned int sz)
{
	unsigned int i, j;
	for(i=0;i<sz-1;i++)
		for (j = i + 1; j < sz; j++)
		{
			if (HuffmanTree[i]->weight > HuffmanTree[j]->weight)
			{
				BiTree tmp = HuffmanTree[i];
				HuffmanTree[i] = HuffmanTree[j];
				HuffmanTree[j] = tmp;
			}

		}
}

void Print(char* str, BiTree huffmantree)
{
	BTStack S;

	while (*str)
	{
		Init(S);
		Traverse_LRD(*str, huffmantree, S);
		printf(" ");
		str++;
	}

}

void Traverse_LRD(char str, BiTree huffmantree, BTStack &S)
{
	if (huffmantree == NULL||str)return;
	Push(S,huffmantree);
	Traverse_LRD(str, huffmantree->lchild, S);
	Traverse_LRD(str, huffmantree->rchild, S);
	unsigned int i = 0;
	if(huffmantree->lchild==NULL&&huffmantree->rchild==NULL&&str==huffmantree->data)
	for (i; i < S.top-1; i++)
	{
		if (S.arr[i]->lchild == S.arr[i + 1])
		{
			printf("0");
		}
		else printf("1");
	}


	Pop(S, huffmantree);
}

void ProductChAndArr(
						const char* str,
						char*		&ch,
						int*		&arr
					)
{
	int hash[127] = {0};
	unsigned int i = 0;
	while (str[i])
	{
		hash[str[i]]++;
		i++;
	}
	unsigned int length = 0;
	for (i = 0; i < 127; i++)
	{
		if (hash[i] != 0)length++;
	}
	ch = (char*)malloc((length+1) * sizeof(char));
	arr = (int*)malloc(length * sizeof(int));
	unsigned int j = 0;
	for (i = 0; i < 127; i++)
	{
		if (hash[i] != 0)
		{
			ch[j] = i;
			arr[j] = hash[i];
			j++;
		}
	}
	ch[j] = '\0';
	arr[j] = '\0';
}



bool Push(BTStack& S, BiTree T)
{
	if (T == NULL)return false;
	if (S.top == MAXSIZE)
		return false;
	S.arr[S.top++] = T;
	return true;
}


bool Pop(BTStack& S, BiTree &T)
{
	if (S.top == S.base)
		return false;
	T = S.arr[--S.top];
	return true;
}


bool IsEmpty(BTStack& S)
{
	if (S.top == S.base)
		return true;
	return false;
}

void Insert(BiTree &T, ElemType e)
{
	int tag = 0;
	BiTree p = T;
	BiTree pre = NULL;

	while (p)
	{
		if (e >= p->data)
		{
			tag = 1;
			pre = p;
			p = p->rchild;
		}
		else
		{
			tag = 0;
			pre = p;
			p = p->lchild;
		}
	}
	Init(p);
	p->data = e;
	if (pre)
	{
		if (tag)
			pre->rchild = p;
		else pre->lchild = p;
	}
	else T = p;
}







bool Init(BTQueue& BTQ)
{
	BTQ.head = BTQ.tail = 0;
	return true;
}

bool IsEmpty(BTQueue BTQ)
{
	if (BTQ.head == BTQ.tail)
		return true;
	return false;
}

bool IsFull(BTQueue BTQ)
{
	if (BTQ.tail + 1 % MAXSIZE == BTQ.head)
		return true;
	return false;
}

bool EnQueue(BTQueue& BTQ, BiTree T)
{

	BTQ.arr[BTQ.tail++] = T;
	BTQ.tail %= MAXSIZE;

	return 0;
}

bool DeQueue(BTQueue& BTQ, BiTree& T)
{
	if (IsEmpty(BTQ))return false;
	else
	{
		T = BTQ.arr[BTQ.head++];
		BTQ.head %= MAXSIZE;
	}
	return true;
}

/*------------------------------Tree.cpp------------------------------*/
//
//三大遍历的非递归算法
//2025年11月29日
//
/*------------------------------Tree.cpp------------------------------*/


void DLRTraversebyLoop(BiTree root)
{
	//
	if (root == NULL)return;
	BTStack S;
	Init(S);
	visit(root);
	Push(S, root);
	int tag = 0;//进出栈 0进 1出
	while (!IsEmpty(S))
	{
		if (tag==0&&root->lchild)//如果当前节点有左子树
		{
			root = root->lchild;//当前节点指向左子树
			visit(root);//打印当前节点
			Push(S, root);//左子树入栈
		}
		else//当前节点为叶子节点,当前节点的左子树已经访问过
		{
			Pop(S, root);//出栈
			tag = 1;
			if (root->rchild)
			{
				root = root->rchild;
				visit(root);
				Push(S, root);
				tag = 0;
			}
			
		}
	}
}
void LDRTraversebyLoop(BiTree root)
{
	if (root == NULL)return;
	BTStack S;
	Init(S);
	Push(S, root);
	int tag = 0;
	while (!IsEmpty(S))
	{
		if (tag == 0 && root->lchild)
		{
			root = root->lchild;
			Push(S, root);
		}
		else
		{
			Pop(S, root);//出栈
			tag = 1;
			visit(root);
			if (root->rchild)
			{
				root = root->rchild;
				Push(S, root);
				tag = 0;
			}
		}
	}
}

void LRDTraversebyLoop(BiTree root)
{
	if (root == NULL)return;
	BTStack S;
	Init(S);
	Push(S, root);
	BiTree pre = NULL;
	while (!IsEmpty(S))
	{
		if (root->lchild&&root->lchild!=pre&&root->rchild!=pre)
		{
			root = root->lchild;
			Push(S, root);
		}
		else if (root->rchild&&root->rchild!=pre)
		{
			root = root->rchild;
			Push(S, root);
		}
		else
		{
			Pop(S, pre);
			visit(pre);
			root = S.arr[S.top - 1];
		}
	}
}

/*------------------------------Tree.cpp------------------------------*/
//
//	以下内容为2025.11.30对二叉树的三大遍历的复盘内容
//
//
//
/*------------------------------Tree.cpp------------------------------*/

void Test_DLR(BiTree T)
{
	if (T == NULL)return;
	BTStack S;
	Init(S);
	BiTree pre = NULL;
	BiTree p = T;
	visit(p);
	Push(S, p);
	while (!IsEmpty(S))
	{
		if (p->rchild!=pre&&p->lchild!=pre&&p->lchild)
		{
			pre = p;
			p = p->lchild;
			visit(p);
			Push(S,p);
		}
		else if (p->rchild!=pre&&p->rchild)
		{
			pre = p;
			p = p->rchild;
			visit(p);
			Push(S, p);
		}
		else
		{
			Pop(S, p);
			pre = p;
			p = S.arr[S.top - 1];
		}
	}
}

void Test_LDR(BiTree T)
{
	if (T == NULL)return;
	BTStack S;
	Init(S);
	int tag = 0;
	BiTree p = T;
	Push(S,p);
	while (!IsEmpty(S))
	{
		if (tag == 0 && p->lchild)
		{
			p = p->lchild;
			Push(S, p);
		}
		else
		{
			Pop(S, p);
			visit(p);
			tag = 1;
			if (p->rchild)
			{
				p = p->rchild;
				Push(S, p);
				tag = 0;
			}
		}
	}
}
void Test_LRD(BiTree T)
{
	if (T == NULL)return;
	BTStack S;
	Init(S);
	BiTree p = T;
	BiTree pre = NULL;
	Push(S, p);
	while (!IsEmpty(S))
	{
		if (p->lchild != pre && p->rchild != pre && p->rchild)
		{
			p = p->lchild;
			Push(S, p);
		}
		else if (p->rchild != pre && p->rchild)
		{
			p = p->rchild;
			Push(S,p);
		}
		else
		{
			Pop(S, p);
			visit(p);
			pre = p;
			p = S.arr[S.top - 1];
		}
	}
}












