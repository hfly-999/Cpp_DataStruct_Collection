//LoopLinkList.h
//HFLY writed
//单向循环链表
//
// head -> node_1 -> node_2 ...... -> node_n +
//  ^										 |
//  |                                        |
//  +----------------------------------------+
//遍历打印√ 初始化 增 删 查 改
#include"Define.h"

struct LoopLinkList
{
	elemtype value;
	LoopLinkList* next;
};

/*初始化*/
status Init(LoopLinkList* L)
{
	
	L->next = L;
	return OK;
}

/*遍历打印*/
status Print(LoopLinkList* L)
{
	LoopLinkList* p = L->next;
	if (p == L)return ERROR;
	while (p != L)
	{
		cout << p->value << " ";
		p = p->next;
	}
	cout << endl;
	return OK;
}


/*在第i个位置插入一个值e*/
status Insert(LoopLinkList* L, int i, elemtype e)
{
	LoopLinkList* p = L;
	LoopLinkList* NewNode = new LoopLinkList();
	NewNode->value = e;
	for (int j = 1; j < i; j++)
	{
		p = p->next;
		if (p == L)return ERROR;
	}
	NewNode->next = p->next;
	p->next = NewNode;
	return OK;
}


/*删除第i个元素*/
status Delete(LoopLinkList* L, int i)
{
	LoopLinkList* p = L;//取得头结点
	if (i < 1)return ERROR;//如果删除位置小于1,直接返回错误
	for (int j = 1; j < i; j++)
	{
		p = p->next;
		if (p == L)return ERROR;//如果返回到头结点,直接返回错误
	}//找到要被删除的节点的前一个结点
	LoopLinkList* part= p->next->next;
	delete p->next;
	p->next = part;
	return OK;
}

/*查找第i个元素*/
elemtype FindElem(LoopLinkList* L, int i)
{
	LoopLinkList* p = L;
	for (int j = 0; j < i; j++)
	{
		p = p->next;
		if (p == L)return ERROR;
	}
	return p->value;
}

/*查找e在循环链表链表当中是否存在,并且返回其在链表当中的位置*/
int GetElem(LoopLinkList* L,elemtype e)
{
	LoopLinkList* p = L;
	int i = 0;
	while (p->next != L)
	{
		p = p->next;
		i++;
		if (p->value == e)
		{
			return i;
		}
	}
	return i;
}

/*改变第i个节点上的值为e*/
status ChangeValue(LoopLinkList* L, int i, elemtype e)
{
	LoopLinkList* p = L;
	if (p->next == L)return ERROR;//如果是空循环链表
	for (int j = 0; j < i; j++)
	{
		p = p->next;
		if (p == L)return ERROR;
	}
	p->value = e;
	return OK;
}
/*总计105行代码*/