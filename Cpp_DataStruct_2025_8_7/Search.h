#pragma once
#include"Define.h"

typedef struct
{
	KeyType		key;//关键字域
	int			p;//下标域
	int			high;//当前树的高度
	int			BF;//平衡因子
}elemtype;

typedef struct
{
	elemtype*	R;//表的基地址
	int			length;//表长
}SSTable;
/*-------------------------Search.h-------------------------*/
typedef struct BSTNode
{
	elemtype	data;
	BSTNode*	left,
		   *	right;
	
}BSTNode,*BSTree;//二叉排序树

typedef struct BSTStack
{
	BSTNode*	data[MAXSIZE];
	int			base,
				top;
}BSTStack;
/*-------------------------Search.h-------------------------*/
//红黑树
typedef struct RBNode
{
	int		key;
	RBNode* lchild;
	RBNode* rchild;
	RBNode* parent;
	int		color;
}RBNode,*RBTree;

typedef struct RBTStack
{
	RBNode *data[MAXSIZE];
	int		base,
			top;
}RBStack;
/*-------------------------Search.h-------------------------*/
//n阶B树
typedef struct BNode
{

	BNode*		parent;
	BNode*		son[N];
	KeyType		data[N];
	int			ElemNum;
}BNode,*BTree;







/*-------------------------Search.h-------------------------*/
//开放地址哈希+顺序递增哈希di=1,2,3,4...n
typedef struct HList
{
	KeyType	*	List;
	int			length;
}HList;




/*-------------------------Search.h-------------------------*/
//拉链法哈希
typedef struct HLNode
{
	KeyType		key;
	HLNode*		next;
}HLNode,*HLLinkList;

typedef struct HashList
{
	HLLinkList List[M];
}HashList;

/*-------------------------Search.h-------------------------*/
//基础算法
//顺序查找
int SearchSeq					(SSTable ST, KeyType key);
//二分查找(非递归)
int BinarySearch				(SSTable ST, KeyType key);
//递归
int RecursiveBinarySearch		(SSTable ST, KeyType key);
int Search						(SSTable ST, KeyType key,
								 KeyType left, KeyType right);
//分块查找

/*-------------------------Search.h-------------------------*/
//二叉排序树的构建
void	SeqListTransToBinarySortTree(int data[], int sz, BSTree& T);
void	Insert					(BSTree& T, KeyType key);//增加一个元素 
void	Delete					(BSTree& T, KeyType key);//删除一个元素
bool	Init					(BSTree& T);
void	LDR						(BSTree T);
BSTNode* LDRFindPre				(BSTree T, KeyType key);
void	visit(BSTree T);
//二叉排序树的查找
int		LDRBinarySortTreeSearch	(BSTree T,int e);//中序查找
bool	Init					(BSTStack &S);
bool	Push					(BSTStack& S, BSTNode* e);
bool	Pop						(BSTStack& S, BSTNode** e);
bool	IsEmpty					(BSTStack S);
int		BinarySortTreeSearch	(BSTree T, int e);//二分查找
/*-------------------------Search.h-------------------------*/
//AVL二叉排序树平衡化
void	LRDRenewBSTBF			(BSTree& T);//遍历二叉树并且更新各个节点的BF值
/*-------------------------Search.h-------------------------*/
//红黑树
bool Init						(RBTree &T);
////红黑树的插入1.0
//void Insert		(RBTree& T, KeyType key);
//void RenewRBTree	(RBTree& T, RBTree& son);
//红黑树的插入2.0
void	Insert			(RBTree& T, KeyType key);
void	RenewRBTree		(RBTree& T, RBTree son);
void	LLRevolve		(RBTree& T, RBTree& son, RBTree& father, RBTree& grandfather);
void	LRRevolve		(RBTree& T, RBTree& son, RBTree& father, RBTree& grandfather);
void	RRRevolve		(RBTree& T, RBTree& son, RBTree& father, RBTree& grandfather);
void	RLRevolve		(RBTree& T, RBTree& son, RBTree& father, RBTree& grandfather);
void	ChangeColor		(RBTree T);
void	Delete			(RBTree T, KeyType key);//还没实现红黑树的自平衡机制(待修正)
RBTree	GetLDRPre		(RBTree T, KeyType key);
//红黑树栈
void	Init			(RBTStack &S);
bool	Push			(RBTStack &S, RBNode *e);
bool	Pop				(RBTStack &S, RBTree &e);
bool	IsEmpty			(RBTStack S);
//红黑树下的中序遍历递归版本(先凑合用)
void	LDR				(RBTree T);
/*-------------------------Search.h-------------------------*/
bool	Init			(KeyType key[], int sz, HList& L);
/*-------------------------Search.h-------------------------*/
//拉链法哈希表的构建与检索
bool	Init			(HashList& HL);//初始化
bool	Insert			(KeyType key, HashList& HL);//哈希表插入
bool	Search			(KeyType key, HashList HL);//哈希表查找
/*-------------------------Search.h-------------------------*/
//n阶B树
bool	Init			(BTree& T);

bool	IsOverFlow		(BTree T);//是否上溢

bool	IsUnderFlow		(BTree T);//是否下溢出

bool	IsLeaves		(BTree T);//是否是叶子节点

void	Insert			(BTree& T, KeyType key);//插入算法

int		InsertInThisNode(BTree &T, KeyType key);	//插入在当前节点
													//并且返回在数组当中的下标
bool	Delete			(BTree& T, KeyType key);


void LDR(BTree T);
//408
bool IsBST				(BSTree T);//判断是否是二叉排序树

bool _IsBST				(BSTree T);//递归法判断二叉树是否是二叉排序树

bool IsAVL				(BSTree T,int &h);//判断是否是AVL

void RDLSearchAllElemNOSmallerthank(BSTree T,KeyType k);//从大到小输出不小于k的所有元素

void Test();





