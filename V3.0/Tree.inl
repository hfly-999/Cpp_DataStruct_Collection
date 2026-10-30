
using namespace DSL;



template<typename T>
BTree<T>::~BTree()
{
	BTree<T>::delete_tree(tree);
}
template<typename T>
void BTree<T>::delete_tree(BNode<T>* tree)
{
	if (tree == nullptr)return;
	queue<BNode<T>*>Q;
	Q.push(tree);
	while (!Q.empty())
	{
		BNode<T>* p = Q.front();
		Q.pop();
		if (p->lchild)
			Q.push(p->lchild);
		if (p->rchild)
			Q.push(p->rchild);
		delete p;
	}//层次遍历删除树
}

template<typename T>
bool BTree<T>::Insert(T value, const std::string& op)
{

	BNode<T>* pre = nullptr;
	BNode<T>* p = tree;
	bool dir_l = true;//现在p在pre的方向
	BNode<T>* pre_create_tree = nullptr;
	BNode<T>* create_tree = nullptr;
	bool create_dir_l=true;//第一次创建新节点的方向是否为左
	if (tree == nullptr)//树本来就是空
		p = create_tree = tree = new BNode<T>();
	
	for (auto it = op.begin(); it != op.end(); ++it)
	{
		if (*it == 'l' || *it == 'L')
		{
			pre = p;
			p = p->lchild;
			dir_l = true;//方向为左
			if (p == nullptr)
			{
				p = new BNode<T>();
				pre->lchild = p;//链接新节点
				if (create_tree == nullptr)//如果还没有创造过树
				{
					pre_create_tree = pre;
					create_tree = p;
					create_dir_l = true;
				}
			}
		}
		else if (*it == 'r' || *it == 'R')
		{
			pre = p;
			p = p->rchild;
			dir_l = false;//方向为右
			if (p == nullptr)
			{
				p = new BNode<T>();
				pre->rchild = p;//链接新节点
				if (create_tree == nullptr)//如果还没有创造过树
				{
					pre_create_tree = pre;
					create_tree = p;
					create_dir_l = false;
				}
			}
		}
		else//回滚
		{
			BTree<T>::delete_tree(create_tree);//删除被创造的树
			if (pre_create_tree)
			{
				if (create_dir_l)
					pre_create_tree->lchild = nullptr;
				else 
					pre_create_tree->rchild = nullptr;
			}
		}
	}
	p->val = value;
	return true;
}
template<typename T>
void BTree<T>::PreOrder()const
{
	if (tree == nullptr)return;
	stack<BNode<T>*>S;
	S.push(tree);
	while (!S.empty())
	{
		BNode<T>* p = S.top();
		S.pop();
		p->visit();
		if (p->rchild)
			S.push(p->rchild);
		if (p->lchild)
			S.push(p->lchild);
	}	
}
template<typename T>
void BTree<T>::InOrder()const
{
	if (tree == nullptr)return;
	stack<BNode<T>*>S;
	bool ispush = true;
	S.push(tree);
	while (!S.empty())
	{
		BNode<T>* p = S.top();
		if (p->lchild&&ispush)	
			S.push(p->lchild);
		else
		{
			ispush = false;
			S.pop();
			p->visit();//访问
			if (p->rchild)
			{
				ispush = true;
				S.push(p->rchild);
			}
		}
	}
}
template<typename T>
void BTree<T>::PostOrder()const
{
	if (tree == nullptr)return;
	stack<BNode<T>*>S;
	S.push(tree);
	BNode<T>* pre = nullptr;
	while (!S.empty())
	{
		BNode<T>* p = S.top();
		if (p->lchild&& pre == nullptr)
			S.push(p->lchild);
		else if (p->rchild && p->rchild != pre)
		{
			S.push(p->rchild);
			pre = nullptr;
		}
		else
		{
			pre = p;
			S.pop();
			pre->visit();
		}
	}
}
template<typename T>
void BTree<T>::LevelOrder()const
{
	if (tree == nullptr)return;
	queue<BNode<T>*>Q;
	Q.push(tree);
	while (!Q.empty())
	{
		BNode<T>* p = Q.front();
		Q.pop();
		p->visit();
		if (p->lchild)
			Q.push(p->lchild);
		if (p->rchild)
			Q.push(p->rchild);

	}//层次遍历
}

