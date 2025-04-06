//单向链表
//OneLinkList.h
//	HFLY writed
//
//head->node_1->node_2->.......->node_n-1->node_n->NULL
//遍历 增√ 删√ 查√ 改√
#include"Define.h"

typedef struct OneLinkList
{
	elemtype value;
	OneLinkList* next;
}OneLinkList;

/*单向链表初始化*/
status Init(OneLinkList* L)
{
	if (L == NULL)
	{
		L = new OneLinkList();
		L->next = NULL;
		return OK;
	}
	else return ERROR;
}

/*往表的第i个位置插入一个值*/
status Insert(OneLinkList* L, int i, char value)
{
	OneLinkList* p = L;
	OneLinkList* NewOneLinkList=new OneLinkList();
	NewOneLinkList->value = value;
	for (int j = 1; j < i; j++)
	{
		if (p->next == NULL)return ERROR;
		p = p->next;
	}
	NewOneLinkList->next = p->next;
	p->next = NewOneLinkList;
	return OK;
}

/*单向链表中删除第i个元素*/
status DeleteElem(OneLinkList* L, int i)
{
	OneLinkList* p = L;
	for (int j = 1; j < i; j++)
	{
		if (p->next == NULL)return ERROR;
		p = p->next;
	}
	OneLinkList* rubbish = p->next;
	p->next = p->next->next;
	delete rubbish;
	return OK;
}

/*顺序打印链表*/
status Print(OneLinkList* L)
{
	OneLinkList* p = L->next;
	while (p != NULL)
	{
		cout << p->value << " ";
		p = p->next;
	}
	cout << endl;
	return OK;
}

/*查找一个元素*/
bool FindElem(OneLinkList *L,elemtype e)
{
	if (L == NULL)return false;
	OneLinkList* p = L->next;
	while (p)
	{
		if (p->value == e)return true;
		p = p->next;
	}
	return false;
}

/*改变第i个元素的value*/
status ElemChange(OneLinkList* L, int i, elemtype e)
{
	if (L == NULL)return ERROR;
	OneLinkList* p = L;
	for (int j = 0; j < i; j++)
	{
		if (p == NULL)return ERROR;
		p = p->next;
	}
	p->value = e;
	return OK;
}

/*合并两个单链表*/
status Union(OneLinkList* L1, OneLinkList* L2)
{
	OneLinkList* p = L1;
	if (L1 == NULL)return ERROR;
	while (p->next != NULL)
	{
		p = p->next;
	}
	p->next = L2;
	return OK;
}

/*删除单链表*/
status Erase(OneLinkList* L1)
{
	if (L1 == NULL)return OK;
	OneLinkList* ptr_1 = L1;
	OneLinkList* ptr_2 = L1->next;
	while (ptr_2 != NULL)
	{
		delete ptr_1;
		ptr_1 = ptr_2;
		ptr_2 = ptr_2->next;
	}
	return OK;
}