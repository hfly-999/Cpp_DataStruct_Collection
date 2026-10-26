#pragma once

#include"Stack.h"
bool Init(SeqStack& S)
{
	S.data = (ElemType*)calloc(MAXSIZE, sizeof(ElemType));
	S.base = 0;
	S.top = 0;
	if (S.data)
	{
		printf("");
		return true;
	}
	else
	{
		printf("系统内存不足,分配失败!\n");
		return false;
	}
}

bool Push(SeqStack& S,ElemType e)
{
	if (S.top < MAXSIZE)
	{
		S.data[S.top++] = e;
		return true;
	}
	else
	{
		printf("线性栈已满！！\n");
		return false;
	}
	
}
bool Pop(SeqStack& S, ElemType& e)
{
	if (S.top != S.base)
	{
		e = S.data[S.top - 1];
		S.top--;
		return true;
	}
	else
	{
		printf("线性栈已空！！\n");
		return false;
	}
	

}

void Print(SeqStack S)
{
	while (S.top != S.base)
	{
		printf("%d\n", S.data[S.top - 1]);
		S.top--;
	}
}

bool IsEmpty(SeqStack S)
{
	if (S.base == S.top)
		return true;
	else return false;
}

unsigned int SeqStackGetLength(SeqStack S)
{
	return S.top - S.base;
}

void ClearSeqStack(SeqStack S)
{
	if (S.data)
		S.top = S.base;
	else return;
}

void Destroy(SeqStack S)
{
	free(S.data);
	S.data = NULL;
	S.top = S.base = 0;
}

/*--------------------------------------------------*/
/*链栈*/
bool Init(LinkStack& S)
{
	S = (StackNode*)malloc(sizeof(StackNode));
	if (S)
	{
		S->next = NULL;
		return true;
	}
	return false;
}

bool Push(LinkStack& S, ElemType e)
{
	LinkStack NewNode;
	if (Init(NewNode))
	{
		NewNode->data = e;
		NewNode->next = S;
		S = NewNode;
		return true;
	}
	else return false;

}

void Print(LinkStack S)
{
	
	while (S)
	{
		printf(" %p | %d \n",S,S->data);
		if (S->next)
		{
			printf("		    | \n");
			printf("	            v \n");
		}
		
		S = S->next;
	}
}

bool Pop(LinkStack& S, ElemType &e)
{
	if (S)
	{
		LinkStack rubbish = S;
		e = rubbish->data;
		S = S->next;
		free(rubbish);
		return true;
	}
	else
	{
		printf("栈已空!!\n");
		return false;
	}


}


bool GetTop(BTStack BTK, BiTree& T)
{
	if (IsEmpty(BTK))return false;
	T = BTK.arr[BTK.top-1];
	return true;
}

