#include"Queue.h"

bool Init(SqQueue& Q)
{
	Q.data = (ElemType*)malloc(MAXSIZE * sizeof(ElemType));
	if (Q.data)
	{
		Q.front = Q.rear = 0;
		return true;
	}
	else return false;
}

bool Push(SqQueue& Q,ElemType e)
{
	if (Q.front==Q.rear+1)//队满,少用一块空间
	{
		printf("队满!!\n");
		return false;
	}
	Q.data[Q.rear++] = e;
	Q.rear %= MAXSIZE;
	return true;
}

bool Pop(SqQueue& Q, ElemType& e)
{
	//空队列处理
	if (Q.front == Q.rear)
	{
		printf("队列为空!\n");
		return false;
	}
	else
	{
		e = Q.data[Q.front++];
		Q.front %= MAXSIZE;
		return true;
	}
}

void Print(SqQueue Q)
{
	while (Q.front != Q.rear)
	{
		printf("%d\n", Q.data[Q.front++]);
		Q.front %= MAXSIZE;
	}
}

unsigned int GetSqQueueLength(SqQueue Q)
{
	if (Q.front < Q.rear)return Q.rear - Q.front;
	else return Q.rear + MAXSIZE - Q.front;
}

bool GetHeadElem(SqQueue Q,ElemType &e)
{
	if (Q.front != Q.rear)//队列不为空
	{
		e = Q.data[Q.front];
		return true;
	}
	return false;
}


/*----------------------------------------*/
/*
bool InitLinkQueue(LinkQueue& Q)
{
	Q.front = Q.rear = (QNode*)malloc(sizeof(QNode));
	if (Q.front)
	{
		Q.front->next = NULL;
		return true;
	}
	else return false;
}*/

bool Push(LinkQueue& Q,ElemType e)
{
	QueuePtr NewNode=(QNode*)malloc(sizeof(QNode));
	if (NewNode)
	{
		NewNode->data = e;
		NewNode->next = NULL;
		Q.rear->next = NewNode;
		return true;
	}
	else return false;

}

bool Pop(LinkQueue& Q, ElemType& e)
{
	if (Q.front->next)
	{
		e = Q.front->next->data;
		QueuePtr rubbish = Q.front->next;
		Q.front->next = rubbish->next;
		if (rubbish == Q.rear)Q.rear = Q.front;
		free(rubbish);
		rubbish = NULL;
		return true;
	}
	else return false;
}

void Destroy(LinkQueue& Q)
{
	while (Q.front)
	{
		QueuePtr tmp = Q.front->next;
		free(Q.front);
		Q.front = tmp;
	}
}

bool EnQueue(LinkQueue& Q, ElemType e)
{
	if (Q.front == NULL)//空队列
	{
		Q.rear->data = e;
		Q.front = Q.rear;
		
	}
	else if (Q.rear->next == Q.front)//队满
	{
		QNode* NewNode = (QNode*)malloc(sizeof(QNode));
		if (!NewNode)return false;
		NewNode->next = Q.front;
		Q.rear->next = NewNode;
		NewNode->data = e;
		Q.rear = NewNode;
	}
	else
	{
		Q.rear = Q.rear->next;
		Q.rear->data = e;
	}
	return false;

}

bool DeQueue(LinkQueue& Q, ElemType &e)
{
	if (Q.front == NULL)return false;//没有元素
	if(Q.front==Q.rear)//只有一个元素
	{
		e = Q.front->data;
		Q.front = NULL;
	}
	else
	{
		e = Q.front->data;
		Q.front = Q.front->next;
	}
	return true;
}

bool Init(LinkQueue& Q)
{
	Q.rear = (QNode*)malloc(sizeof(QNode));
	if (!Q.rear)return false;
	Q.rear->next = Q.rear;
	Q.front = NULL;
	return true;
}
bool Print(LinkQueue Q)
{
	QNode* ptr = Q.front;
	if (ptr == NULL)return false;
	while (ptr != Q.rear)
	{
		printf("%d ", ptr->data);
		ptr = ptr->next;
	}
	printf("%d \n", ptr->data);
	return true;
}



