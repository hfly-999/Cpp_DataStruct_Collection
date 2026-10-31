namespace DSL
{
/*----------------------BTree-------------------------------*/
	
	template<typename T>
	void BTree<T>::PreOrder()const
	{
		if (root == nullptr)return;
		stack<BNode<T>*>S;
		S.push(root);
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
		if (root == nullptr)return;
		stack<BNode<T>*>S;
		bool ispush = true;
		S.push(root);
		while (!S.empty())
		{
			BNode<T>* p = S.top();
			if (p->lchild && ispush)
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
		if (root == nullptr)return;
		stack<BNode<T>*>S;
		S.push(root);
		BNode<T>* pre = nullptr;
		while (!S.empty())
		{
			BNode<T>* p = S.top();
			if (p->lchild && pre == nullptr)
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
		if (root == nullptr)return;
		queue<BNode<T>*>Q;
		Q.push(root);
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
/*----------------------BTree-------------------------------
*
*
* 
* 
----------------------ThreadTree--------------------------*/
	







/*----------------------ThreadTree--------------------------*/
}
