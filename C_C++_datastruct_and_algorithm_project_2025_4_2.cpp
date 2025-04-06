#include"OneLinkList.h"
#include"LoopLinkList.h"
int main()
{
	LoopLinkList* L=new LoopLinkList(), * L1 = new LoopLinkList(), * L2 = new LoopLinkList(), * L3 = new LoopLinkList(), * L4 = new LoopLinkList(), * L5 = new LoopLinkList();
	
	L->next = L1;
	L1->value = 'A'; L1->next = L2;
	L2->value = 'B'; L2->next = L3;
	L3->value = 'C'; L3->next = L4;
	L4->value = 'D'; L4->next = L5;
	L5->value = 'E'; L5->next = L;
	Insert(L, 6, 'H');
	Insert(L, 7, 'K');
	Print(L);
	cout<<GetElem(L, 'K')<<endl;
	ChangeValue(L, 3, 'J');
	Print(L);
	return 0;
}
