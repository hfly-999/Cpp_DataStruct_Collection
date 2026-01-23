
#include"Tree.h"



int main()
{
    BTree t1, t2, t3, t4, t5, t6, t7;
    Init(t1);
    Init(t2);
    Init(t3);
    Init(t4);
    Init(t5);
    Init(t6);
    Init(t7);
    t1->data = 1;
    t2->data = 2;
    t3->data = 3;
    t4->data = 4;
    t5->data = 5;
    t6->data = 6;
    t7->data = 7;
    t1->lchild = t2, t1->rchild = t3;
    t2->lchild = t4, t2->rchild = t5;
    t3->lchild = t6, t3->rchild = t7;
    _DLR(t1);
    DLR(t1);
    _LDR(t1);
    LDR(t1);
    _LRD(t1);
    LRD(t1);
    LevelReverse(t1);
    cout << CountNode(t1) << endl;
    cout << GetTreeHeight(t1) << endl;
    cout << CountLeaves(t1) << endl;
    return 0;
}