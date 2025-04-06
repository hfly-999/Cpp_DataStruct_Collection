//双向循环链表
//DuLoopLinkList.h
//HFLY writed
//tail <=> head <=> node_1 <=> node_2......node_n <=> tail
//增 删 查 改

#include"Define.h"

typedef struct
{
	elemtype value;
	DuLinkList *rear;
	DuLinkList *next;
}DuLinkList;

/*在第i个位置插入*/
status Insert(DuLinkList *DL,int i,elemtype e)
{
	if (DL == NULL)return ERROR;

	return OK;
}
