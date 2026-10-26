#pragma once
#include"Search.h"

int SearchSeq(SSTable ST, KeyType key)
{
	ST.R[0].key = key;
	int i;
	for (i = ST.length; ST.R[i].key != key; i--);
	return i;
}

int BinarySearch(SSTable ST, KeyType key)
{
	int left = 1;
	int right = ST.length;
	int mid = (left + right) / 2;
	while (left <= right)
	{
		if (key < ST.R[mid].key)//在左边
		{
			right = mid-1;
			mid = (left + right) / 2;
		}
		else if (key > ST.R[mid].key)
		{
			left = mid+1;
			mid = (left + right) / 2;
		}
		else return mid;
	}
	return 0;
}

int RecursiveBinarySearch(SSTable ST, KeyType key)
{
	return Search(ST, key, 1, ST.length);
}
int Search(SSTable ST, KeyType key, KeyType left, KeyType right)
{
	if (right > left)return 0;//没查找到
	int mid = (left + right) / 2;
	if (ST.R[mid].key < key)//在右边
	{
		return Search(ST, key, mid + 1, right);
	}
	else if (ST.R[mid].key > key)
	{
		return Search(ST, key, left, mid - 1);
	}
	return mid;
}

bool Init(BSTree& T)
{
	T = (BSTNode*)malloc(sizeof(BSTNode));
	if (T)
	{
		T->data.p = 0;
		T->left = T->right = NULL;
		T->data.high = 0;
		T->data.BF = 0;
		T->data.key = 0;

		return true;
	}
	return false;
}

void SeqListTransToBinarySortTree(int data[], int sz, BSTree& T)
{
	T->data.key = data[0];
	int i = 1;
	BSTree p;
	while (i < sz)
	{
		p = T;//从根节点出发
		while (true)
		{
			if (data[i] >= p->data.key)
			{
				if(p->right)
				{
					p = p->right;
				}
				else
				{
					BSTNode* NewNode;
					Init(NewNode);
					p->right = NewNode;
					NewNode->data.p = i;
					NewNode->data.key = data[i++];
					break;
				}
			}
			else
			{
				if (p->left)
				{
					p = p->left;
				}
				else
				{
					BSTNode* NewNode;
					Init(NewNode);
					p->left = NewNode;
					NewNode->data.p = i;
					NewNode->data.key = data[i++];
					break;
				}
			}

		}
	}
}

void LDR(BSTree T)
{
	if (T==NULL)return;
	
	LDR(T->left);
	visit(T);
	LDR(T->right);
}

void visit(BSTree T)
{
	printf("%d ", T->data.key);
}

int LDRBinarySortTreeSearch(BSTree T,int e)
{
	if (!T)return 0;
	BSTStack S;
	Init(S);
	Push(S, T);//入栈
	BSTNode* p = T;
	int tag = 0;//上一次的操作为入栈
	while (!IsEmpty(S))
	{
		if (p->left&&tag==0)//如果上一次为入栈,并且入栈元素有左子树
		{
			Push(S, p->left);
			p = p->left;
		}
		else//如果没有左子树,或者上次为出栈操作
		{
			Pop(S, &p);//出栈
			tag = 1;
			//visit
			if (p->data.key == e)return p->data.p;
			if (p->right)
			{
				Push(S, p->right);
				p = p->right;
				tag = 0;
			}
		}
	}
	return 0;

}

bool Init(BSTStack& S)
{
	S.base = S.top = 0;
	return true;
}
bool Push(BSTStack& S, BSTNode* e)
{
	if (S.top == MAXSIZE)
		return false;
	S.data[S.top++] = e;
	return true;
}

bool Pop(BSTStack& S, BSTNode** e)
{
	if (S.base == S.top)
		return false;
	*e = S.data[--S.top];
	return true;
}

bool IsEmpty(BSTStack S)
{
	if (S.base == S.top)return true;
	return false;
}

int BinarySortTreeSearch(BSTree T, int e)
{
	if (T == NULL)return -1;
	while (T->data.key != e)
	{
		if (e > T->data.key)
			T = T->right;
		else T = T->left;
		if (T == NULL)return -1;
	}
	return T->data.p;
}
/*-------------------------Search.h-------------------------*/
//void Insert(BSTree& T, KeyType key)
////{
//	if (T == NULL)
//	{
//		Init(T);
//		T->data.key = key;
//		return;
//	}
//	else
//	{
//		BSTNode* p = T;
//		BSTNode* preNode = NULL;
//		BSTStack S;
//		Init(S);
//		int tag = -1;
//		while (p)
//		{
//			if (key >= p->data.key)
//			{
//				Push(S, p);
//				tag = 1;
//				preNode = p;
//				p = p->right;
//			}
//			else
//			{
//				Push(S, p);
//				tag = 0;
//				preNode = p;
//				p = p->left;
//			}
//		}
//		Init(p);
//		Push(S, p);
//		p->data.key = key;
//		if (tag == 1)
//			preNode->right = p;
//		else
//			preNode->left = p;
//		LRDRenewBSTBF(T);
//		for (int i = S.top - 1; i >= 0; i--)
//		{
//			if (S.data[i]->data.BF < -1 || S.data[i]->data.BF>1)
//			{
//				BSTNode* Father = NULL;
//				if (i > 0)
//				{
//					Father = S.data[i - 1];
//				}
//				BSTNode* A = S.data[i];
//				BSTNode* B = S.data[i + 1];
//				BSTNode* C = S.data[i + 2];
//				if (A->left == B && B->left == C)//LL
//				{
//					BSTNode* Bright = B->right;
//					B->right = A;
//					A->left = Bright;
//					if (Father)
//					{
//						if (Father->left == A)Father->left = B;
//						else Father->right = B;
//
//					}
//					else T = B;
//				}
//				else if (A->right == B && B->right == C)//RR
//				{
//					BSTNode* Bleft = B->left;
//					B->left = A;
//					A->right = Bleft;
//					if (Father)
//					{
//						if (Father->left == A)Father->left = B;
//						else Father->right = B;
//
//					}
//					else T = B;
//				}
//				else if (A->left == B && B->right == C)//LR
//				{
//					BSTNode* Cleft = C->left;
//					BSTNode* Cright = C->right;
//					C->left = B;
//					C->right = A;
//					B->right = Cleft;//这里不是B->right=C->left,此时C->left已经被赋值为B
//					A->left = Cright;//
//					if (Father)
//					{
//						if (Father->left == A)Father->left = C;
//						else Father->right = C;
//
//					}
//					else T = C;
//				}
//				else//RL
//				{
//					BSTNode* Cleft = C->left;
//					BSTNode* Cright = C->right;
//					C->left = A;
//					C->right = B;
//					A->right = Cleft;
//					B->left = Cright;
//					if (Father)
//					{
//						if (Father->left == A)Father->left = C;
//						else Father->right = C;
//					}
//					else T = C;
//				}
//				LRDRenewBSTBF(T);
//				break;
//			}
//		}
//	}
//}
void Insert(BSTree& T, KeyType key)
{
	if (T == NULL)//空树
	{
		Init(T);
		T->data.key = key;
		LRDRenewBSTBF(T);
	}else{
		BSTNode* p = T;//树指针
		BSTStack S;//栈
		Init(S);//初始化栈
		int pre = -1;
		while (p)//直到指针为空
		{
			if (key >= p->data.key)
			{
				Push(S, p);
				p = p->right;

				pre = 1;
			}
			else
			{
				Push(S, p);
				p = p->left;
				pre = 0;
			} 
		}
		Init(p);
		p->data.key = key;
		if (pre)
			S.data[S.top - 1]->right = p;
		else S.data[S.top - 1]->left = p;
		Push(S, p);
	
		if (S.top - S.base >= 3)//有三个节点及以上时
		{
			LRDRenewBSTBF(T);
			for (int i = S.top - 3; i >= 0; i--)
			{

				if (S.data[i]->data.BF < -1 || S.data[i]->data.BF>1)
				{
					BSTNode* tree = NULL;
					BSTNode* A = S.data[i];
					BSTNode* B = S.data[i + 1];
					BSTNode* C = S.data[i + 2];

					if (i >= 1)
					{
						tree = S.data[i - 1];
						if (tree->left == A)pre = 0;
						else pre = 1;
					}
					if (A->left == B && B->left == C) {//LL
						if (tree)
						{
							if (pre)
								tree->right = B;
							else tree->left = B;
						}
						else T = B;
						BSTNode* Bright = B->right;
						B->right = A;
						A->left = Bright;
					}
					else if (A->right == B && B->right == C)
					{//RR
						if (tree)
						{
							if (pre)
								tree->right = B;
							else tree->left = B;
						}
						else T = B;
						BSTNode* Bleft = B->left;
						B->left = A;
						A->right = Bleft;
					}
					else if (A->left == B && B->right == C) {//LR
						if (tree)
						{
							if (pre)
								tree->right = C;
							else tree->left = C;
						}
						else T = C;
						BSTNode* Cleft = C->left;
						BSTNode* Cright = C->right;
						C->left = B;
						C->right = A;
						B->right = Cleft;
						A->left = Cright;
					}
					else {//RL
						if (tree)
						{
							if (pre)
								tree->right = C;
							else tree->left = C;
						}
						else T = C;
						BSTNode* Cleft = C->left;
						BSTNode* Cright = C->right;
						C->left = A;
						C->right = B;
						A->right = Cleft;
						B->left = Cright;
					}
					LRDRenewBSTBF(T);
					break;
				}
			}
			
		}

	}
}
/*-------------------------Search.h-------------------------*/
void Delete(BSTree& T, KeyType key)
{
	if (!T)return;
	if (T->data.key == key)
	{
		free(T);
		T = NULL;
	}
	BSTNode* p=T, * pre = NULL;
	int tag = 0;//表示左右
	while (p && p->data.key != key)
	{
		if (key >= p->data.key)
		{
			tag = 1;
			pre = p;
			p = p->right;
		}
		else
		{
			tag = 0;
			pre = p;
			p = p->left;
		}
	}
	if (p == NULL)return;//没有这个节点
	else if (p->left == NULL && p->right == NULL)//叶子结点
	{
		if (tag == 0)
			pre->left = NULL;
		else pre->right = NULL;
		free(p);
		p = NULL;
	}
	else
	{
		pre = LDRFindPre(T, p->data.key);//pre为中序遍历下的p的前驱节点
		KeyType tmp = pre->data.key;
		Delete(T, tmp);
		p->data.key = tmp;
	}
	LRDRenewBSTBF(T);
	
}

BSTNode* LDRFindPre(BSTree T, KeyType key)
{
	if (T == NULL)return NULL;//没有前驱
	BSTStack S;
	Init(S);
	BSTree pre = NULL;
	BSTree p=T;
	Push(S, p);
	int tag = 0;
	while (!IsEmpty(S))
	{
		if (tag == 0 && p->left)
		{
			p = p->left;
			Push(S, p);
		}
		else
		{
			Pop(S, &p);
			if (p->data.key == key)return pre;
			pre = p;
			if (p->right)
			{
				tag = 0;
				p = p->right;
				Push(S, p);
			}
		}
	}
	return NULL;

}

void LRDRenewBSTBF(BSTree& T)
{
	if (T == NULL)return;
	LRDRenewBSTBF(T->left);
	LRDRenewBSTBF(T->right);
	if (T->left == NULL && T->right == NULL)//叶子节点
	{
		T->data.high = 1;
		T->data.BF = 0;
	}
	else if (T->right == NULL)//只有左子树
	{
		T->data.high = T->left->data.high + 1;
		T->data.BF = T->left->data.high;
	}
	else if (T->left == NULL)//只有右子树
	{
		T->data.high = T->right->data.high + 1;
		T->data.BF = -(T->right->data.high);
	}
	else
	{
		T->data.high = T->left->data.high > T->right->data.high ? T->left->data.high + 1 : T->right->data.high + 1;
		T->data.BF = T->left->data.high - T->right->data.high;
	}


}

bool Init(HashList& HL)
{
	for (int i = 0; i < M; i++)
	{
		HL.List[i] = NULL;
	}
		
	return true;
}

bool Insert(KeyType key, HashList& HL)
{
	int mod = key % M;
	if (HL.List[mod] == NULL)
	{
		HL.List[mod] = (HLNode*)malloc(sizeof(HLNode));
		if (HL.List[mod])
		{
			HL.List[mod]->next = NULL;
			HL.List[mod]->key = key;
		}
		else return false;
	}
	else
	{
		HLNode* NewNode = (HLNode*)malloc(sizeof(HLNode));
		if (NewNode)
		{
			NewNode->key = key;
			NewNode->next = HL.List[mod];
			HL.List[mod] = NewNode;
		}
		else return false;
	}
	return true;
}

bool Search(KeyType key, HashList HL)
{
	int mod = key % M;
	HLNode* p = HL.List[mod];
	while (p)
	{
		if (p->key == key)return true;
		p = p->next;
	}
	return false;
}


bool Init(KeyType key[], int sz, HList& L)
{
	L.length = 2 * sz;
	L.List = (KeyType*)malloc(L.length * sizeof(KeyType));
	if (L.List)
	{
		for (int i = 0; i < L.length; i++)
			L.List[i] = -1;
		for (int i = 0; i < sz; i++)
		{
			KeyType mod = key[i] % M;
			if (L.List[mod] == -1)
			{
				L.List[mod] = key[i];
			}
			else
				for (int j = mod + 1; j < L.length; j++)
					if (L.List[j] == -1)
					{
						L.List[j] = key[i];
						break;
					}
		}
		return true;
	}
	return false;
}

bool Init(RBTree& T)
{
	T = (RBNode*)malloc(sizeof(RBNode));
	if (T == NULL)return false;
	T->lchild = T->rchild = T->parent = NULL;
	T->key = -1;
	return true;
}
/*-------------------------Search.h-------------------------*/
//
//	红黑树1.0 Insert()
//
//
/*-------------------------Search.h-------------------------*/
//void Insert(RBTree& T,KeyType key)
//{
//	if (T == NULL)//空树
//	{
//		Init(T);
//		T->key=key;
//		T->color = 0;
//		RenewRBTree(T,T);
//	}
//	else//非空树
//	{
//		RBTStack S;
//		Init(S);
//		RBNode*	father=NULL;//父亲节点
//		RBNode*	son = T;//儿子节点
//		int tag=-1;
//		while (son) 
//		{
//			if (key >= son->key)
//			{
//				Push(S,son);
//				father=son;
//				son = son->rchild;
//				tag=1;//p
//			}
//			else
//			{
//				Push(S, son);
//				father=son;
//				son = son->lchild;
//				tag=0;
//			}
//			
//		}
//		Init(son);
//		son->key=key;//赋值关键值
//		if(tag)
//			father->rchild=son;
//		else 
//			father->lchild=son;
//		son->parent = father;
//		son->color = 1;
//		RenewRBTree(T,son);
//	}
//}
/*-------------------------Search.h-------------------------*/
//
// 1.0 RenewRBTree
// 
/*-------------------------Search.h-------------------------*/
//void RenewRBTree(RBTree& T, RBTree& son)
//{
//	if (T == son)
//	{
//		son->color = 0;//如果是根节点之间染黑即可
//	}
//	else//插入处为非根节点
//	{
//		RBTree father = son->parent;//父节点
//		RBTree grandfather = NULL;
//		if (father)
//			grandfather = father->parent;
//		RBTree tree = NULL;
//		if (grandfather)
//			tree = grandfather->parent;
//
//		if (father->color)//如果不满足红黑树的性质:不红红
//		{
//			if ((grandfather->lchild == father && (grandfather->rchild == NULL || grandfather->rchild->color == 0))
//				|| (grandfather->rchild == father && (grandfather->lchild == NULL || grandfather->lchild->color == 0))
//				)//叔叔为黑色
//			{
//				if (grandfather->lchild == father && father->lchild == son)//LL 父爷染色
//				{
//					//树指针重定向
//					if (tree == NULL)//爷爷为树根
//						T = father;
//					else if (tree->lchild == grandfather)//爷爷为左子树
//						tree->lchild = father;
//					else tree->rchild = father;//爷爷为右子树
//					//旋转
//					RBTree fatherright = father->rchild;//father右子树进行记录
//					father->rchild = grandfather;//father右子树指向爷爷
//					grandfather->lchild = fatherright;
//					//父指针重定向
//					father->parent = tree;
//					grandfather->parent = father;
//					if (fatherright)//如果父亲原来有右子树
//						fatherright->parent = grandfather;
//					//染色
//					father->color = !father->color;//父亲颜色取反
//					grandfather->color = !grandfather->color;//爷爷颜色取反
//				}
//				else if (grandfather->rchild == father && father->rchild == son)//RR 父爷染色
//				{
//					//树指针重定向
//					if (tree == NULL)//爷爷为树根
//						T = father;
//					else if (tree->lchild == grandfather)//爷爷为左子树
//						tree->lchild = father;
//					else tree->rchild = father;//爷爷为右子树
//					//旋转
//					RBTree fatherleft = father->lchild;
//					father->lchild = grandfather;
//					grandfather->rchild = fatherleft;
//					//父指针重定向
//					father->parent = tree;
//					grandfather->parent = father;
//					if (fatherleft)
//						fatherleft->parent = grandfather;
//					//染色
//					father->color = !father->color;//父亲颜色取反
//					grandfather->color = !grandfather->color;//爷爷颜色取反
//				}
//				else if (grandfather->lchild == father && father->rchild == son)//LR 儿爷染色
//				{
//					//树指针重定向
//					if (tree == NULL)
//						T = son;
//					else if (tree->lchild == grandfather)//爷爷为左子树
//						tree->lchild = son;
//					else tree->rchild = son;
//					//旋转
//					RBTree son_left = son->lchild;
//					RBTree son_right = son->rchild;
//					son->lchild = father;
//					son->rchild = grandfather;
//					father->rchild = son_left;
//					grandfather->lchild = son_right;
//					//父指针重定向
//					if (son_left)
//						son_left->parent = father;
//					if (son_right)
//						son_right->parent = grandfather;
//					grandfather->parent = father->parent = son;
//					son->parent = tree;
//					//染色son和grandfather
//					son->color = !son->color;
//					grandfather->color = !grandfather->color;
//				}
//
//				else if (grandfather->rchild == father && father->lchild == son)//RL 儿爷染色
//				{
//					//树指针重定向
//					if (tree == NULL)
//						T = son;
//					else if (tree->lchild == grandfather)//爷爷为左子树
//						tree->lchild = son;
//					else tree->rchild = son;
//					//旋转
//					RBTree son_left = son->lchild;
//					RBTree son_right = son->rchild;
//					son->lchild = grandfather;
//					son->rchild = father;
//					grandfather->rchild = son_left;
//					father->lchild = son_right;
//					//父指针重定向
//					if (son_left)
//						son_left->parent = grandfather;
//					if (son_right)
//						son_right->parent = father;
//					grandfather->parent = father->parent = son;
//					son->parent = tree;
//					//染色son和grandfather
//					son->color = !son->color;
//					grandfather->color = !grandfather->color;
//				}
//				else cout << "error" << endl;
//			}
//			else //叔叔为红色
//			{
//				//叔父爷染色
//				grandfather->color = !grandfather->color;//爷爷
//				grandfather->lchild->color = !grandfather->lchild->color;//叔父
//				grandfather->rchild->color = !grandfather->rchild->color;//叔父
//				RenewRBTree(T, grandfather);//对爷爷节点进行更新
//			}
//		}
//	}
//}
/*-------------------------Search.h-------------------------*/
//
//	红黑树2.0 Insert()
//
//
/*-------------------------Search.h-------------------------*/
void Insert(RBTree& T, KeyType key)
{
		RBTree pre = NULL;
		RBTree p = T;
		int tag = 0;
		while (p)
		{
			if (key>=p->key)
			{
				tag = 1;//往右
				pre = p;
				p = p->rchild;
			}
			else
			{
				tag = 0;//往左
				pre = p;
				p = p->lchild;
			}
		}
		Init(p);
		p->color = 1;
		p->key = key;
		p->parent = pre;
		if (T)
		{
			if (tag)
				pre->rchild = p;
			else pre->lchild = p;
		}
		else
		{
			T = p;
		}
		RenewRBTree(T,p);//更新红黑树的颜色
	
}

void RenewRBTree(RBTree& T, RBTree son)
{
	if (son->parent==NULL)
	{
		son->color = 0;//如果节点为根节点,颜色设置为黑色
	}
	else
	{
		RBTree father = NULL;
		RBTree grandfather = NULL;
		father = son->parent;
		grandfather = father->parent;
		if (father->color)//如果父亲的颜色为红色
		{
			if (grandfather->lchild == father && father->lchild == son)//LL形
			{
				if (grandfather->rchild==NULL||grandfather->rchild->color==0)//叔叔为黑色
				{
					LLRevolve(T,son,father,grandfather);//进行LL旋转
					ChangeColor(father);
					ChangeColor(grandfather);
				}
				else//如果叔叔为红色
				{
					//叔父爷变色
					ChangeColor(grandfather);
					ChangeColor(grandfather->lchild);
					ChangeColor(grandfather->rchild);
					RenewRBTree(T, grandfather);
				}
			}
			else if (grandfather->rchild==father&&father->rchild==son)//RR形
			{
				if (grandfather->lchild==NULL || grandfather->lchild->color==0)//叔叔为黑色
				{
					RRRevolve(T, son, father, grandfather);
					ChangeColor(grandfather);
					ChangeColor(father);
				}
				else//如果叔叔为红色
				{
					//叔父爷变色
					ChangeColor(grandfather);
					ChangeColor(grandfather->lchild);
					ChangeColor(grandfather->rchild);
					RenewRBTree(T, grandfather);
				}
			}
			else if (grandfather->lchild==father&&father->rchild==son)//LR形
			{
				if (grandfather->rchild==NULL || grandfather->rchild->color==0)//叔叔为黑色
				{		
					LRRevolve(T, son, father, grandfather);
					//爷孙变色
					ChangeColor(grandfather);
					ChangeColor(son);
				}
				else//如果叔叔为红色
				{
					//叔父爷变色
					ChangeColor(grandfather);
					ChangeColor(grandfather->lchild);
					ChangeColor(grandfather->rchild);
					RenewRBTree(T, grandfather);
				}
			}
			else//RL形
			{
				if (grandfather->lchild==NULL || grandfather->lchild->color==0)//叔叔为黑色
				{
					
					RLRevolve(T, son, father, grandfather);
					//爷儿变色
					ChangeColor(grandfather);
					ChangeColor(son);
				}
				else//如果叔叔为红色
				{
					//叔父爷变色
					ChangeColor(grandfather);
					ChangeColor(grandfather->lchild);
					ChangeColor(grandfather->rchild);
					RenewRBTree(T, grandfather);
				}
			}
		}
	}
}

void LLRevolve(RBTree& T, RBTree& son, RBTree& father, RBTree& grandfather)
{
	RBTree pre = grandfather->parent;
	//LR ptr
	if (pre == NULL)
		T = father;
	else
	{
		if (pre->lchild == grandfather)
			pre->lchild = father;
		else pre->rchild = father;
	}
	RBTree father_right = father->rchild;
	father->rchild = grandfather;
	grandfather->lchild = father_right;
	//parent ptr
	if (father_right)
	father_right->parent = grandfather;
	father->parent = pre;
	grandfather->parent = father;
	
}

void RRRevolve(RBTree& T, RBTree& son, RBTree& father, RBTree& grandfather)
{
	RBTree pre = grandfather->parent;
	//LR ptr
	if (pre == NULL)
		T = father;
	else
	{
		if (pre->lchild == grandfather)
			pre->lchild = father;
		else pre->rchild = father;
	}
	RBTree father_left = father->lchild;
	father->lchild = grandfather;
	grandfather->rchild = father_left;
	//parent ptr
	father->parent = pre;
	if(father_left)
	father_left->parent = grandfather;
	grandfather->parent = father;
	
}

void LRRevolve(RBTree& T, RBTree& son, RBTree& father, RBTree& grandfather)
{
	
	RBTree pre = grandfather->parent;
	if (pre == NULL)
		T = son;
	else
	{
		if (pre->lchild == grandfather)
			pre->lchild = son;
		else pre->rchild = son;
	}
	//LRptr
	RBTree son_left = son->lchild;
	RBTree son_right = son->rchild;
	son->lchild = father;
	son->rchild = grandfather;
	father->rchild = son_left;
	grandfather->lchild = son_right;
	//parentptr
	son->parent = pre;
	if(son_left)
	son_left->parent = father;
	if(son_right)
	son_right->parent = grandfather;
	father->parent = son;
	grandfather->parent = son;
	
}

void RLRevolve(RBTree& T, RBTree& son, RBTree& father, RBTree& grandfather)
{
	
	RBTree pre = grandfather->parent;
	if (pre == NULL)
		T = son;
	else
	{
		if (pre->lchild == grandfather)
			pre->lchild = son;
		else pre->rchild = son;
	}
	
	
	RBTree son_left = son->lchild;
	RBTree son_right = son->rchild;
	son->lchild = grandfather;
	son->rchild = father;
	father->lchild = son_left;
	grandfather->rchild = son_right;
	//parentptr
	son->parent = pre;
	if(son_left)
	son_left->parent = father;
	if(son_right)
	son_right->parent = grandfather;
	father->parent = son;
	grandfather->parent = son;
	
}

bool IsBST(BSTree T)
{
	BSTree pre = NULL;
	BSTree p = T;
	BSTStack S;
	Init(S);
	int tag = 0;
	Push(S, p);
	while (!IsEmpty(S))
	{
		if (tag == 0 && p->left)
		{
			p = p->left;
			Push(S,p);
		}
		else
		{
			//visit
			Pop(S, &p);
			tag = 1;
			if (pre)
			{
				if (pre->data.key > p->data.key)
					return false;
			}
			pre = p;
			if (p->right)
			{
				p = p->right;
				Push(S, p);
				tag = 0;
			}
		}
	}
	return true;
}


void ChangeColor	(RBTree T)
{
	if(T)
	T->color = !T->color;
}



void Init(RBTStack &S)
{
	S.base=S.top=0;
}

bool Push(RBTStack &S, RBNode *e)
{
	if(S.top==MAXSIZE)return false;//栈满
	S.data[S.top++]=e;
	return true;
}
bool Pop(RBTStack &S, RBTree &e)
{
	if(S.top==S.base)return false;//栈空
	e=S.data[--S.top];
	return true;
}
bool IsEmpty(RBTStack S)
{
	if(S.top==S.base)return true;
	return false;
}

void LDR(RBTree T)
{
	if(T==NULL)return;
	LDR(T->lchild);
	//visit
	if (T->color)
	{
		if (T->parent)
			printf("key:%d color:红 parent:%-6d", T->key, T->parent->key);
		else printf("key:%d color:红 NULL", T->key);
	}
	else
	{
		if (T->parent)
			printf("key:%d color:黑 parent:%-6d", T->key, T->parent->key);
		else printf("key:%d color:黑 NULL", T->key);
	}
	if (T->lchild == NULL || T->lchild->color == 0)
		printf("黑 ");
	else printf("红 ");
	if (T->rchild == NULL || T->rchild->color == 0)
		printf("黑 ");
	else printf("红 ");
	cout << endl;
	LDR(T->rchild);
	return;
}

void Delete(RBTree T, KeyType key)
{
	if (T == NULL)return;
	RBTree p = T;
	RBTree pre = NULL;
	int tag = 0;
	while (p && p->key != key)
	{
		if (key > p->key)
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
	if (p == NULL)return;//不存在要删除的节点
	if (p->lchild == NULL && p->rchild == NULL)//叶子节点直接删除即可
	{
		if (pre)
		{
			if (tag)
				pre->rchild = NULL;
			else pre->lchild = NULL;
		}
		free(p);
		p = NULL;
	}
	else
	{
		pre = GetLDRPre(T, key);//中序下的前驱节点
		KeyType tmp = pre->key;
		Delete(T, tmp);
		p->key = tmp;
	}

}

RBTree	GetLDRPre		(RBTree T, KeyType key)
{
	if (T == NULL)return NULL;
	RBTStack S;
	Init(S);
	int tag = 0;
	RBTree p = T;
	Push(S, p);
	RBTree pre = NULL;
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
			if (p->key == key)return pre;
			pre = p;
			if(p->rchild)
			{ 
				p = p->rchild;
				tag = 0;
				Push(S, p);
			}
		}
	}
	return NULL;
}
KeyType _predt = MAX_INT_16;
bool _IsBST				(BSTree T)
{
	bool left, right;
	if (T == NULL)return true;
	left = _IsBST(T->left);
	if (left == false || _predt > T->data.key)
		return false;
	_predt = T->data.key;
	right = _IsBST(T->right);
	return right;
}

bool IsAVL				(BSTree T,int &h)
{
	bool bl, br;
	int hl=0, hr=0;
	if (T == NULL)
	{
		h = 0;
		return true;
	}
	bl = IsAVL(T->left,hl);
	br = IsAVL(T->right,hr);
	h = hl > hr ? (hl + 1) : (hr + 1);
	if (bl && br)
	{
		if (hl - hr <= 1 && hl - hr >= -1)
			return true;
		else return false;
	}
	else return false;
}

void RDLSearchAllElemNOSmallerthank(BSTree T, KeyType k)
{
	if (T == NULL)return;
	RDLSearchAllElemNOSmallerthank(T->right, k);
	if (T->data.key >= k)visit(T);
	RDLSearchAllElemNOSmallerthank(T->left, k);
}
/*-------------------------Search.h-------------------------*/
bool Init(BTree& T)
{
	T			=	(BTree)		malloc(sizeof(BNode));
	if (T == NULL)return false;
	T->ElemNum	=	0;
	T->parent	=	NULL;
	for (int i = 0; i <N; i++)
	{
		T->data[i]	=	MAX_INT_16;
		T->son[i]	=	NULL;
	}
	return true;
}

bool IsOverFlow(BTree T)
{
	if (T->ElemNum == N)
		return true;
	return false;
}

bool IsUnderFlow(BTree T)
{
	if (T->parent == NULL)return false;//根节点
	if (T->ElemNum < (N+1) / 2 - 1)return true;
	return false;
}

bool IsLeaves(BTree T)
{
	if (T == NULL)return true;
	for (int i = 0; i < N ; i++)
		if (T->son[i])return false;
	return true;
}






void LDR(BTree T)
{
	if (T == NULL)return;

	for (int i = 0; i < T->ElemNum; i++)
	{
		LDR(T->son[i]);
		printf("%d ", T->data[i]);
	}
	LDR(T->son[T->ElemNum]);
}







































