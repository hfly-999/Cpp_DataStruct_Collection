#pragma once

#include"Define.h"

typedef struct BTNode
{
    ElemType    data;
    BTNode      * lchild,//左孩子指针
                * rchild;//右孩子指针

}BTNode, * BTree;

typedef struct BTStack
{
    BTNode      ** data;
    int            base,
                   top;
}BTStack;

typedef struct BTQueue
{
    BTNode  **data;
    int     front,
            rear;
};
//------------------Tree.h------------------//
bool Init       (BTree& T);

void visit      (BTree T);

void _DLR       (BTree T);
void DLR        (BTree T);

void _LDR       (BTree T);
void LDR        (BTree T);

void _LRD       (BTree T);
void LRD        (BTree T);

//二叉树层次遍历
void LevelReverse   (BTree T);
//------------------Tree.h------------------//
//BTStack

//二叉树栈初始化
bool Init       (BTStack& S);

//二叉树节点栈是否为空
bool IsEmpty    (BTStack S);

//判断二叉树节点栈是否满
bool IsFull     (BTStack S);

//入二叉树节点栈
bool Push       (
                 BTStack& S,
                 BTree& btnode
                );

//出二叉树节点栈
bool Pop        (
                 BTStack& S,
                 BTree& btnode
                );

//得到栈顶元素
BTree GetTop    (BTStack S);

//------------------Tree.h------------------//

//初始化二叉树队列
bool Init       (BTQueue& Q);

//进队
bool EnQueue    (BTQueue& Q, BTree T);

//出队
bool DeQueue    (BTQueue& Q, BTree& T);

//判断队列是否为空
bool IsEmpty    (BTQueue Q);

//判断是否队满
bool IsFull     (BTQueue Q);

//------------------Tree.h------------------//

//统计二叉树节点数目
int CountNode   (BTree T);

//统计二叉树当中的叶子节点数目
int CountLeaves(BTree T);

//获取树的高度
int GetTreeHeight   (BTree T);
