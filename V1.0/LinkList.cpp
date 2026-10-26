#include"LinkList.h"

bool Init(LinkList& L)
{
	L = (LNode*)malloc(sizeof(LNode));
	if (L == NULL)return false;
	L->next = NULL;
	return true;
}

bool LinkListInsert(LinkList& L, int i, ElemType e)
{
	LNode* ptr = L;
	i--;
	while (i && ptr)
	{
		i--;
		ptr = ptr->next;
	}
	if (!ptr)return false;//插入位置错误
	LNode* NewNode;
	Init(NewNode);
	NewNode->next = ptr->next;
	ptr->next = NewNode;
	NewNode->data = e;
	return true;
}

void Print(LinkList L)
{
	if (L == NULL)
	{
		cout << "This is a void LinkList!!!" << endl;
		return;
	}
	L = L->next;
	while (L)
	{
		if (sizeof(ElemType) == 1)
			printf("%c ", L->data);
		else if (sizeof(ElemType) == 4)
			printf("%d ", L->data);
		L = L->next;
	}
	cout << endl;
}



bool BF_Is_B_Son_of_A(LinkList A, LinkList B)
{
	A = A->next;
	B = B->next;
	while (A)
	{
		while (A->data != B->data)
		{
			A = A->next;
			if (!A)return false;
		}
		LNode* tmpB = B;
		while (A->data == tmpB->data)
		{
			A = A->next;
			tmpB = tmpB->next;
			if (!tmpB)return true;
			if (!A)return false;
		}


	}
	return false;
}

bool IsEqual_Loop_DLinklist(DLinkList L)
{
	DNode* ptr1 = L->prior;
	DNode* ptr2 = L->next;
	while (ptr1 != ptr2)
	{
		if (ptr1->data == ptr2->data)
		{
			ptr1 = ptr1->prior;
			ptr2 = ptr2->next;
		}
		else return false;
	}
	return true;
}

bool Init(DLinkList& L)
{
	L = (DNode*)malloc(sizeof(DNode));
	if (!L)return false;
	L->next =L->prior= L;
	return true;
}

bool DLinkListInsert(DLinkList& L, int i, ElemType e)
{
	DNode* ptr = L;
	i--;
	while (i)
	{
		i--;
		ptr = ptr->next;
		if (ptr == L)return false;
	}
	DNode* NewNode;
	Init(NewNode);
	NewNode->data = e;
	NewNode->next = ptr->next;
	ptr->next->prior = NewNode;
	NewNode->prior = ptr;
	ptr->next = NewNode;
	return true;
}



bool KMP_Is_B_Son_of_A(LinkList A, LinkList B)
{
	LNode* ptrB_left = B, * ptrB_right;
	unsigned int B_length = 0;
	while (ptrB_left)
	{
		ptrB_left = ptrB_left->next;
		B_length++;
	}
	unsigned int* next = (unsigned int*)malloc(B_length*sizeof(unsigned int));
	next[0] = 0;
	B_length = 1;//记录ptrA_right在next数组当中的下标
	unsigned int tmp = 0;//最长公共前后缀长度
	ptrB_right = B->next;//A
	while (ptrB_right)
	{
		ptrB_left = B->next;//B的左指针
		for (unsigned int i = 0; i < tmp; i++)
			ptrB_left = ptrB_left->next;
		if (ptrB_left->data == ptrB_right->data)
		{
			tmp++;
			next[B_length++] = tmp;
			ptrB_right = ptrB_right->next;
		}
		else
		{
			if (tmp == 0)
			{
				next[B_length++] = tmp;
				ptrB_right = ptrB_right->next;
			}
			else
			{
				tmp = next[B_length - 1];
			}
		}

	}
	ptrB_left = B->next;
	A = A->next;
	unsigned int j = 0;//B链表的长度
	while (A)
	{
		if (A->data == ptrB_left->data)
		{
			j++;
			A = A->next;
			ptrB_left = ptrB_left->next;
		}
		else
		{
			if (ptrB_left != B->next)
			{
				j = next[j - 1];
				ptrB_left = B->next;
				for (unsigned int k = 0; k < j; k++)
					ptrB_left = ptrB_left->next;
			}
			else
			{
				A = A->next;
			}
		}
		if (!ptrB_left)return true;
	}
	return false;
}


bool LinkListDelx(LinkList& L, ElemType x)
{
	if (!L)return false;
	LinkList ptr = L;
	while (ptr->next)
	{
		if (ptr->next->data == x)
		{
			LNode* rubbish = ptr->next;
			ptr->next = ptr->next->next;
			free(rubbish);
		}
		else ptr = ptr->next;
	}
	return true;

}


bool LinKListDelMinValue(LinkList& L)
{
	if (!L)return false;
	ElemType min = L->next->data;
	LNode* pre = L;
	LNode* ptr = L;//操作副本
	while (ptr->next)
	{
		if (min > ptr->next->data)
		{
			min = ptr->next->data;
			pre = ptr;
		}
		else ptr = ptr->next;
	}
	LNode* rubbish = pre->next;
	pre->next = pre->next->next;
	free(rubbish);


	return false;
	
}

bool LinkListReverse(LinkList& L)
{
	if (!L)return false;
	LNode* tail = L;
	while (tail->next)tail = tail->next;
	while (L->next != tail)
	{
		LNode* tmp = L->next;
		L->next = L->next->next;
		tmp->next = tail->next;
		tail->next = tmp;
	}
	return true;
}

bool LinkListDel_s_to_t(LinkList& L, ElemType s, ElemType t)
{
	if (!L)return false;
	LinkList ptr = L;
	while (ptr->next)
	{
		if (ptr->next->data >= s && ptr->next->data <= t)
		{
			ptr->next = ptr->next->next;
		}
		else ptr = ptr->next;
	}
	return true;
}

LNode* FindPublicNode(LinkList A, LinkList B)
{
	LNode* tmpA = A;
	unsigned int lenA = 0;
	while (tmpA)
	{
		tmpA = tmpA->next;
		lenA++;
	}
	LNode* tmpB = B;
	unsigned int lenB = 0;
	while (tmpB)
	{
		tmpB = tmpB->next;
		lenB++;
	}
	if (lenA > lenB)
	{
		int i;
		for (i = 0; i < lenA - lenB; i++)A = A->next;
		for (i = 0; i < lenB; i++)
		{
			if (A == B)return A;
			A = A->next;
			B = B->next;
		}
	}
	else
	{
		int i;
		for (i = 0; i < lenB - lenA; i++)B = B->next;
		for (i = 0; i < lenA; i++)
		{
			if (A == B)return A;
			A = A->next;
			B = B->next;
		}

	}
	return NULL;
}

void DivideCtoAandB(LinkList& C, LinkList& A, LinkList& B)
{
	LNode* ptrA = A,*tmp;
	B->next = NULL;
	while (C->next)
	{
		ptrA->next = C->next;
		ptrA = ptrA->next;
		C->next = C->next->next;
		tmp = C->next;
		C->next = C->next->next;
		tmp->next = B->next;
		B->next = tmp;
	}
	ptrA->next = NULL;
}

bool DelTheSame(LinkList& L)
{
	if (!L)return false;
	LNode* ptr = L->next;
	while (ptr->next)
	{
		if (ptr->data == ptr->next->data)
		{
			LNode* rubbish = ptr->next;
			ptr->next = ptr->next->next;
			free(rubbish);
		}
		else
		{
			ptr = ptr->next;
		}
	}
	return true;
}



bool CombineAandBtoC(LinkList& A, LinkList& B, LinkList& C)
{
	if (!A && !B)return false;
	LNode* ptrA = A->next, *ptrB = B->next, *ptrC = C;
	while (ptrA && ptrB)
	{
		if (ptrA->data < ptrB->data)// B大
			ptrA = ptrA->next;
		else if (ptrA->data == ptrB->data)
		{
			LNode* NewNode = (LNode*)malloc(sizeof(LNode));
			if (!NewNode)return false;
			NewNode->data = ptrA->data;
			NewNode->next = ptrC->next;
			ptrC->next = NewNode;
			ptrC = ptrC->next;
			ptrA = ptrA->next;
			ptrB = ptrB->next;
		}
		else
			ptrB = ptrB->next;
	}
	return true;
}

void CombineAandB(LinkList& A, LinkList& B)
{
	LNode* tmpA = A, * tmpB = B->next;
	while (tmpA->next && tmpB)
	{
		if (tmpA->next->data < tmpB->data)tmpA->next = tmpA->next->next;
		else if (tmpA->next->data == tmpB->data)
		{
			tmpA = tmpA->next;
			tmpB = tmpB->next;
		}
		else
		{
			tmpB = tmpB->next;
		}
	}
}

bool IsBSonofA(LinkList A, LinkList B)
{
	LNode* tmpA = A->next, * tmpB = B->next;//工作指针
	while (tmpA->data != tmpB->data)tmpA = tmpA->next;
	while (tmpA)
	{
		LNode* ptrA = tmpA,*ptrB=tmpB;//比较指针A,B
		while (ptrA && ptrA->data == ptrB->data)
		{
			ptrA = ptrA->next;
			ptrB = ptrB->next;
			if (!ptrB)return true;//比对成功
		}
		tmpA = tmpA->next;
	}
	return false;

}



void right_move(LinkList& L, int k)
{
	LNode* left = L, * right;
	int i, n=0;
	while (left)
	{
		left = left->next;
		n++;
	}
	left = L;
	for (i = 0; i < n - k - 1; i++)left = left->next;
	right = left->next;
	left->next = NULL;
	LNode* tmp = right;
	while (tmp->next)tmp = tmp->next;
	tmp->next = L;
	L = right;
}

LNode* IsLinkListHasCircle(LinkList L)
{
	LNode* slow = L, * fast = L;//设立两个快慢指针
	while (fast != NULL && fast->next != NULL)//当链表非空并且fast指针后继结点不为空时
	{
		slow = slow->next;//慢指针走一步
		fast = fast->next->next;//快指针走两步
		if (slow == fast)break;//相遇
	}
	if (fast->next == NULL)return NULL;
	LNode* p1 = L, * p2 = fast;
	while (p1 != p2)
	{
		p1 = p1->next;
		p2 = p2->next;
	}
	return p1;
}

bool IsBalance(LinkList L, int n)
{
	LNode* ptr = L;//工作指针
	ElemType* stack = (ElemType*)malloc((n / 2) * sizeof(ElemType));
	int i;
	for (i = 0; i < n / 2; i++)
	{
		stack[i] = ptr->data;
		ptr = ptr->next;
	}
	if (n % 2 == 1)
	{
		ptr = ptr->next;
	}
	i--;
	while (ptr||i==0)
	{
		if (stack[i] == ptr->data)
		{
			i--;
			ptr = ptr->next;
		}
		else return false;
		
	}
	if (!ptr && i == 0)return true;
	return false;
	
}












