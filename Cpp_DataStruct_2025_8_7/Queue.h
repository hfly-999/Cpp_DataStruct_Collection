#pragma once
#include"Define.h"
#include"Tree.h"

/*------------------------------Queue-----------------------------*/
//顺序队列的定义
typedef struct SqQueue
{
	ElemType* data;
	int front;//队头
	int rear;//队尾
}SqQueue;




//链式队列的定义(链队列带头结点)
//结点定义
typedef struct QNode
{
	ElemType data;
	QNode* next;
}QNode, * QueuePtr;//结构体类型,结构体指针类型
//链式队列定义
typedef struct
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;//

/*------------------------------Queue-----------------------------*/

/*--------------------链队列---------------------*/
//初始化链队列
bool Init		(LinkQueue& Q);
//入链队列
bool Push		(LinkQueue& Q, ElemType e);
//出链队列
bool Pop		(LinkQueue& Q, ElemType& e);
//销毁链队列
void Destroy	(LinkQueue& Q);

bool Print		(LinkQueue Q);

bool EnQueue	(LinkQueue& Q, ElemType e);

bool DeQueue	(LinkQueue& Q, ElemType &e);

/*-----------------------------------------------*/

/*-------------------线性队列---------------------*/
//初始化线性队列
bool Init		(SqQueue &Q);
//入线性队列
bool Push		(SqQueue& Q,ElemType e);
//出线性队列
bool Pop		(SqQueue& Q, ElemType& e);
//打印线性队列
void Print		(SqQueue Q);
//求线性队列的长度
unsigned int GetSqQueueLength(SqQueue Q);
//取线性队列的队头元素
bool GetHeadElem(SqQueue Q,ElemType &e);
/*-------------------------------------------------*/




