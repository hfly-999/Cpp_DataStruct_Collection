#pragma once
#include"Define.h"
#include"LinkList.h"


/*------------------------------Tree------------------------------*/
//顺序二叉树的定义
typedef ElemType SqBiTree[MAXSIZE];

/*------------------------------Tree------------------------------*/
//二叉树的链式定义
typedef struct BiNode
{
	ElemType		data;
	int				weight;//权
	struct BiNode*	lchild,
				 *	rchild;
}BiNode, * BiTree;

/*------------------------------Tree------------------------------*/
//三叉树的链式定义
typedef struct TriTNode
{
	ElemType data;
	struct TriTNode* lchild,
				   * rchild,
				   * parent;
}TriTNode, * TriTree;
/*------------------------------Tree------------------------------*/
//线索二叉树
typedef struct ThreadNode
{
	ElemType data;
	struct ThreadNode*	lchild,
					 *	rchild;
	int ltag, rtag;
}ThreadNode, * ThreadTree;
/*------------------------------Tree------------------------------*/
//派生类型,顺序二叉树栈
typedef struct BTStack
{
	BiTree			arr[MAXSIZE];
	unsigned int	top;
	unsigned int	base;
}BTStack;

/*------------------------------Tree------------------------------*/
//树的双亲表示法
typedef struct PTNode
{
	ElemType	data;
	int			parent;//父节点位置
}PTNode;
typedef struct
{
	PTNode	nodes[MAXSIZE];
	int		r,
			n;//记录根结点位置和元素个数
}PTree;



/*------------------------------Tree------------------------------*/
//树的子链表表示法
typedef struct CTNode
{
	int				child;
	struct CTNOde*	next;
}*ChildPtr;
typedef struct
{
	ElemType		data;
	ChildPtr		firstchild;
}CTBox;
typedef struct
{
	CTBox			nodes[MAXSIZE];
	int				n,
					r;//结点数与根节点位置
}CTree;


/*------------------------------Tree------------------------------*/

typedef struct CSNode
{
	ElemType		data;
	struct CSNode*	firstchild,
				 *	nextsibling;//分别指向当前结点的第一个孩子与下一个兄弟
}CSNode, * CSTree;
/*------------------------------Tree------------------------------*/
typedef struct
{
	int				weight;
	int				parent,
					lch,
					rch;
}HTNode,* HuffmanTree;

//顺序树队列
typedef struct BTQueue
{
	BiTree			arr[MAXSIZE];
	unsigned int	head;
	unsigned int	tail;
}BTQueue;



/*------------------------------Tree.h------------------------------*/

/*------------------------------Tree.h------------------------------*/
//基本算法
//树节点的初始化
bool Init				(BiTree& BT);

bool visit				(BiTree Node);

bool Traverse_DLR		(BiTree root);			//先根遍历

void DLRTraversebyLoop	(BiTree root);			//非循环下的先根遍历

bool Traverse_LDR		(BiTree root);			//中根遍历

void LDRTraversebyLoop	(BiTree root);			//中根遍历非递归

bool Traverse_LRD		(BiTree root);			//后根遍历

void LRDTraversebyLoop	(BiTree root);			//非循环下的后根遍历

bool LeverOrder			(BiTree root);			//二叉树的层次遍历

bool FoundBinaryTree	(BiTree& BT);//先序建立二叉树

bool Copy				(BiTree& BT, BiTree& NewBT);//复制二叉树

unsigned int Count		(BiTree BT);//递归计算节点总个数

unsigned int CountLeaves(BiTree BT);//递归计算叶子结点个数

bool Init				(BTStack& T);

bool Push				(BTStack& S, BiTree T);

bool Pop				(BTStack& S, BiTree &T);

bool IsEmpty			(BTStack& S);

void Insert				(BiTree &T, ElemType e);
/*------------------------------Tree------------------------------*/
//顺序队列存放树节点的有关算法
bool Init				(BTQueue& BTQ);

bool IsEmpty			(BTQueue BTQ);

bool IsFull				(BTQueue BTQ);

bool EnQueue			(BTQueue& BTQ, BiTree T);			//入队列,允许空指针入队列

bool DeQueue			(BTQueue& BTQ, BiTree& T);

/*------------------------------Tree------------------------------*/
//线索二叉树有关算法
//线索二叉树结点的初始化
bool Init				(ThreadTree& T);//初始化线索二叉树

bool visit				(ThreadTree& Node, ThreadTree& pre);//访问线索二叉树的结点

bool Traverse_DLR		(ThreadTree root);					//递归中序遍历线索二叉树


bool InThread_LDR		(ThreadTree &root,ThreadTree &pre);	//线索二叉树中序线索化

bool CreateInThread		(ThreadTree& T);					//二叉树线索化完全封装后的函数

bool SeqTraverse		(ThreadTree root);					//顺序DLR访问线索二叉树
/*------------------------------Tree------------------------------*/
//408
//递归法求树的深度
unsigned int GetDepth		(BiTree T);
//非递归法求树的高度
unsigned int GetDepth_while(BiTree root);

//判断一颗二叉树是否是完全二叉树P152 T04(你的写法是错误的)
//答案的思路:层次遍历
bool IsCompleteBinaryTree	(BiTree T);


//求二叉树当中的n2
unsigned int Count_n_2		(BiTree T);

//交换所有节点的左右子树
void ExchangeLeftAndRight	(BiTree T);

//判断两颗二叉树是否相似
//相似条件两颗二叉树为空,或者都只有一个根节点;或者T1与T2左子树相似,T1与T2右子树相似
bool IsSimilar				(BiTree T1, BiTree T2);


void DelXInTheTree			(BiTree T, ElemType x);//删除值为x的子树

void DeleteXTree			(BiTree T);//递归法删除树

void FindXAncestor			(BiTree T,ElemType x);//找到x的祖先

void testFindXAncestor		(BiTree T, ElemType x);

void FindMostCloseSameAncestor(BiTree root, BiTree p, BiTree q, BiTree& r);

void Reverse_LRD			(BiTree root, BiTree p, BiTree q, BiTree& r);

void LinkLeavesNode			(BiTree T, LinkList head);//从左到右连接叶子结点
//计算二叉树的带权路径长度
unsigned int CalWPL			(BiTree T);
void CalWPL_Traverse_LRD	(BiTree T,BTStack S,unsigned int &ret);

//对于满二叉树先序pre转后序post
void PreTransPost			(ElemType *pre,ElemType *post);
void PreTransPost_shift		(ElemType pre[], unsigned int left, unsigned right);


//把二叉树转换为中缀表达式LDR
void TranslateBiTreeToLDRExpress(BiTree T,BiTree root);
void BiTreeTranslateToLDRExpree(BiTree T, unsigned int depth);//标准写法


/*------------------------------Tree.cpp------------------------------*/
void Test_DLR(BiTree T);
void Test_LDR(BiTree T);
void Test_LRD(BiTree T);
/*------------------------------Tree.cpp------------------------------*/
//哈夫曼树



BiTree CreateHuffmanTree(const char* ch, const int* arr);			//已知词谱和词频,构建哈夫曼树


void SortHuffmanTree	(BiTree* HuffmanTree,unsigned int sz);		//对哈夫曼树进行排序 按从小到大


void Print				(char* str, BiTree huffmantree);			//对一段文字进行加密


void Traverse_LRD		(char str,BiTree huffmantree,BTStack &S);	//后序遍历哈夫曼树


void ProductChAndArr	(const char* str, char* &ch, int* &arr);	//根据一段文字自动生成词谱数组和词频数组
