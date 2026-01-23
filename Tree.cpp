#include"Tree.h"

void visit(BTree T)
{
    if (T)
        cout << T->data << " ";
}
void _DLR(BTree T)//非递归式先根遍历二叉树
{
    if (T == NULL)return;
    visit(T);
    _DLR(T->lchild);
    _DLR(T->rchild);
}
void DLR(BTree T)
{
    if (T == NULL)return;
    BTree p = T;//工作指针
    BTStack S;
    Init(S);
    visit(p);//访问根节点
    Push(S, p);//根节点进栈
    int tag = 0;//表示上一次操作为进栈操作
    while (!IsEmpty(S))
    {
        if (tag == 0 && p->lchild)//上一次为入栈操作,并且入栈元素有左子树
        {
            p = p->lchild;
            visit(p);//访问左子树
            Push(S, p);//左子树进栈
        }
        else
        {
            Pop(S, p);
            tag = 1;
            if (p->rchild)//如果出栈元素有右子树
            {
                p = p->rchild;//
                visit(p);
                Push(S, p);
                tag = 0;
            }
        }
    }
    cout << endl;
}

void _LDR(BTree T)
{
    if (T == NULL)return;
    _LDR(T->lchild);
    visit(T);
    _LDR(T->rchild);
}

void LDR(BTree T)
{
    if (T == NULL)return;
    BTStack S;
    Init(S);
    BTree p = T;
    Push(S, p);
    while (!IsEmpty(S))
    {
        if (p->lchild)
        {
            p = p->lchild;
            Push(S, p);
        }
        else
        {
            Pop(S, p);//出栈
            visit(p);//访问出栈元素
            if (p->rchild)
            {
                p = p->rchild;
                Push(S, p);
            }

        }
    }
    cout<<endl;
}

void _LRD(BTree T)
{
    if (T == NULL)return;
    _LRD(T->lchild);
    _LRD(T->rchild);
    visit(T);
}
void LRD(BTree T)
{
    if (T == NULL)return;
    BTStack S;
    Init(S);
    BTree p = T;//工作指针
    BTree pre = NULL;//上一个访问的元素
    int tag = 0;//0表示进栈,1表示退栈
    Push(S, p);
    while (!IsEmpty(S))
    {
        p = GetTop(S);//p为栈顶元素
        if (p->lchild && p->lchild != pre&&tag==0)//如果栈顶元素有左子树并且上一个访问的元素不是左子树并且上一次的操作是进栈操作
        {
            p = p->lchild;
            Push(S, p);
        }
        else if (p->rchild && p->rchild != pre&&tag==1)//如果栈顶元素有右子树，并且右子树不是上一个访问的节点，并且上一次为出栈操作
        {
            p = p->rchild;
            Push(S, p);
            tag = 0;
        }
        else//如果栈顶元素没有左右子树
        {
            Pop(S, p);//出栈
            visit(p);
            pre = p;//记录访问节点
            tag = 1;//出栈
        }
    }
    cout << endl;
}




bool Init(BTStack& S)
{
    S.data = (BTNode**)malloc(MAXSIZE * sizeof(BTNode*));
    if (S.data == NULL)return false;
    S.top = S.base = 0;
    return true;
}

bool IsEmpty(BTStack S)//二叉树节点栈是否为空
{
    if (S.base == S.top)return true;
    return false;
}

bool IsFull(BTStack S)
{
    if (S.top == MAXSIZE)return true;
    return false;
}

bool Push(BTStack& S, BTree& btnode)
{
    if (IsFull(S) == true)return false;
    S.data[S.top++] = btnode;
    return true;
}

bool Pop(BTStack& S, BTree& btnode)
{
    if (IsEmpty(S) == true)return false;
    btnode = S.data[--S.top];
    return true;
}

bool Init(BTree& T)
{
    T = (BTNode*)malloc(sizeof(BTNode));
    if (T)
    {
        T->lchild = T->rchild = NULL;
        return true;
    }

    return false;
}

BTree GetTop(BTStack S)
{
    if (IsEmpty(S) == true)return NULL;
    return S.data[S.top - 1];
}

bool Init(BTQueue& Q)
{
    Q.data = (BTNode**)malloc(MAXSIZE * sizeof(BTNode*));
    Q.front = Q.rear = 0;
    if (Q.data)return true;
    else       return false;
}

bool EnQueue(BTQueue& Q, BTree T)
{
    if (IsFull(Q))return false;
    Q.data[Q.rear++] = T;
    Q.rear %= MAXSIZE;
    return true;
}

bool DeQueue(BTQueue& Q, BTree& T)
{
    if (IsEmpty(Q))return false;
    T = Q.data[Q.front++];
    Q.front %= MAXSIZE;
    return true;
}

bool IsEmpty(BTQueue Q)
{
    if (Q.front == Q.rear)return true;
    return false;
}

bool IsFull(BTQueue Q)
{
    if ((Q.rear + 1) % MAXSIZE == Q.front)return true;
    return false;
}

void LevelReverse(BTree T)
{
    BTQueue Q;//二叉树节点队列
    Init(Q);//初始化
    BTree p = T;//临时指针
    EnQueue(Q, p);//根节点入队
    while (!IsEmpty(Q))//当队列不为空的时候
    {
        DeQueue(Q, p);//出队列
        visit(p);//访问出队列元素
        if (p->lchild)EnQueue(Q, p->lchild);//如果出队列元素有左孩子，则左孩子入队列
        if (p->rchild)EnQueue(Q, p->rchild);//如果出队列元素有右孩子，则右孩子入队列
    }
    cout << endl;
}

int CountNode(BTree T)
{
    if (T == NULL)return 0;
    return 1 + CountNode(T->lchild) + CountNode(T->rchild);
}

int GetTreeHeight(BTree T)
{
    if (T == NULL)return 0;
    int LHeight = GetTreeHeight(T->lchild);//左子树高度
    int RHeight = GetTreeHeight(T->rchild);//右子树高度
    return 1 + (LHeight > RHeight ? LHeight : RHeight);
}

int CountLeaves(BTree T)
{
    if (T == NULL)return 0;
    if (T->lchild == NULL && T->rchild == NULL)return 1;
    return CountLeaves(T->lchild) + CountLeaves(T->rchild);
}