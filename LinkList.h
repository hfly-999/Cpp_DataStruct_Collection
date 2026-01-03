#pragma once
#include"Define.h"
//单链表
typedef struct LNode
{
	ElemType		data;
	struct LNode*	next;
}LNode, * LinkList;
//双链表
typedef struct DNode
{
	ElemType		data;
	struct DNode	* prior,
					* next;
}DNode,*DLinkList;

/*--------------------------------------------------------------------------------*/
//简单算法										




								  
//单链表的初始化																	  
bool Init			(LinkList& L);													  
//(带头结点)单链表在某一位置进行插入												  
bool LinkListInsert	(LinkList& L, int i, ElemType e);                              
//(带头结点)对单链表进行打印
void Print			(LinkList L);
//双链表的初始化
bool Init			(DLinkList& L);
//循环双链表插入元素
bool DLinkListInsert(DLinkList& L, int i,ElemType e);

/*--------------------------------------------------------------------------------*/
//较为复杂的算法题目

//(带头结点)判断B链表是否为A链表的连续子链表
bool BF_Is_B_Son_of_A		(LinkList A,LinkList B);
//(带头结点)判断B链表是否为A链表的连续子链表
bool KMP_Is_B_Son_of_A		(LinkList A, LinkList B);

//判断一个循环双链表是否对称
bool IsEqual_Loop_DLinklist	(DLinkList L);

//在带头结点的单链表当中删除值为x的元素
bool LinkListDelx			(LinkList& L, ElemType x);

//删除带头结点的单链表当中的最小值(单链表有最小值而且唯一)
bool LinKListDelMinValue	(LinkList& L);

//带头结点单链表就地置逆
bool LinkListReverse		(LinkList& L);

//删除从s到t的所有结点
bool LinkListDel_s_to_t		(LinkList& L, ElemType s, ElemType t);

//找到两个链表的首个公共结点,如果没有则返回NULL
LNode* FindPublicNode		(LinkList A, LinkList B);

//将带头结点的链表(a1,b1,....an,bn)拆为(a1,a2,...an)和(bn,bn-1,...b1)
void DivideCtoAandB			(LinkList& C, LinkList& A, LinkList& B);

//带头结点单链表去重
bool DelTheSame				(LinkList& L);

//两个带头结点的单链表A B(递增有序)找公共元素产生链表C
bool CombineAandBtoC		(LinkList& A, LinkList& B, LinkList& C);

//两个带头结点有序递增单链表A B求交集到A
void CombineAandB			(LinkList& A, LinkList& B);

//判断链表B是否是A的子链表BF算法
bool IsBSonofA				(LinkList A, LinkList B);

//在不带头结点的单链表当中进行右移k个单位
void right_move				(LinkList& L, int k);

//判断一个单链表是否有环,并且返回入环点
LNode* IsLinkListHasCircle	(LinkList L);

//判断一个单链表是否对称
bool IsBalance				(LinkList L, int n);//n为单链表长度































/*--------------------------------------------------------------------------------*/