//#include"Tree.h"
//using namespace DSL;
//
//
//
//
//
//
////构造函数
//template<typename type>
//BNode<type>::BNode(
//	type value,
//	BNode<type>* lchild,
//	BNode<type>* rchild
//) :
//	val(value),
//	lchild(lchild),
//	rchild(rchild)
//{
//
//}
//
////拷贝构造
//template<typename type>
//BNode<type>::BNode(const BNode& obj) :
//	val(obj.val),
//	lchild(nullptr),
//	rchild(nullptr)
//{
//	if (obj.lchild)
//		lchild = new BNode(*obj.lchild);
//	if (obj.rchild)
//		rchild = new BNode(*obj.rchild);
//}
//
//
//
//
//
//
//
//
////递归析构
//template<typename type>
//BNode<type>::~BNode()
//{
//	if (lchild)
//		delete lchild;
//	if (rchild)
//		delete rchild;
//}
//
//
//template<typename type>
//void BNode<type>::Setlchild(BNode<type>* lchild)
//{
//	this->lchild = lchild;//设置左子树
//}
//
//
//
//template<typename type>
//BNode<type>*& BNode<type>::leftchild()const
//{
//	return this->lchild;
//}
//
//
//
//
//
//template<typename type>
//void BNode<type>::Setrchild(BNode<type>* rchild)
//{
//	this->rchild = rchild;//设置右子树
//}
//
//
//
//template<typename type>
//BNode<type>*& BNode<type>::rightchild()const
//{
//	return rchild;
//}
//
//
//template<typename type>
//void BNode<type>::Setlchildnullptr()
//{
//	Setlchild(nullptr);
//}
//
//
//
//
//
//template<typename type>
//void BNode<type>::Setrchildnullptr()
//{
//	Setrchild(nullptr);
//}
//
//
//
//
//
//template<typename type>
//void BNode<type>::visit()const
//{
//	
//	std::cout << (void*)this << ":" << this->val<<std::endl;
//	if (this->lchild)
//		std::cout <<"	this.lchild:" << (void*)this->lchild << ":" << this->lchild->val << std::endl;
//	else 
//		std::cout <<"	this.rchild:" << "nullptr" << std::endl;
//	if (this->rchild)
//		std::cout <<"	this.rchild:" << (void*)this->rchild << ":" << this->rchild->val << std::endl;
//	else 
//		std::cout <<"	this.rchild:" << "nullptr" << std::endl;
//
//}
//
//
//
//
//
//
//
//
//template<typename type>
//void BNode<type>::SetValue(type value)
//{
//	this->val = value;
//}
//
//
//
//
//
//template<typename type>
//type& BNode<type>::SetValue()const
//{
//	return this->val;
//}
//
//
//
//
//template<typename type>
//type BNode<type>::GetValue()const
//{
//	return val;
//}
//
//
//
//
//
//template<typename type>
//BNode<type>* BNode<type>::Getlchild()const
//{
//	return	this->lchild;
//}
//
//
//
//
//
//template<typename type>
//BNode<type>* BNode<type>::Getrchild()const
//{
//	return this->rchild;
//}
//
//
///*----------------------------Tree.h---------------------------*/
//
//
//
//template<typename type>
//BTree<type>::BTree(type value) :
//	T(new BNode<type>(value)) {}
//
//template<typename type>
//BTree<type>::BTree(BNode<type>* T) :
//	T(T) {
//	if (T == nullptr)
//		T = new BNode<type>();
//}
//
//template<typename type>
//BTree<type>::BTree(const BTree& obj) :
//	T(new BNode<type>(*obj.T)) {}
//template<typename type>
//BTree<type>::~BTree()
//{
//	delete T;
//}
//
//
//
//template<typename type>
//bool BTree<type>::Insert(type value, const std::string op)
//{
//	size_t i = 0;
//	BNode<type>* pre = nullptr;
//	BNode<type>* p = T;
//	bool Direction = false;
//	BNode<type>* preCreatTree = nullptr;
//	BNode<type>* CreatTree = nullptr;
//	bool IsCreatTree = false;
//	bool CreatTreeDirection = false;//默认左边创建树
//	while (op[i])
//	{
//		if (op[i] == 'l' || op[i] == 'L')
//		{
//			pre = p;
//			p = p->Getlchild();
//			Direction = false;//方向往左
//		}
//		else if (op[i] == 'r' || op[i] == 'R')
//		{
//			pre = p;
//			p = p->Getrchild();
//			Direction = true;//方向往右
//		}
//		else//操作非法
//		{
//			delete CreatTree;
//			if (CreatTreeDirection)//右边为新树right
//				preCreatTree->Setrchildnullptr();
//			else preCreatTree->Setlchildnullptr();//left
//			return false;
//		}
//
//		if (p == nullptr)//如果p是空树
//		{
//			p = new BNode<type>();//申请内存
//			if (Direction)//right
//				pre->Setrchild(p);
//			else pre->Setlchild(p);//left
//			if (IsCreatTree == false)
//			{
//				IsCreatTree = true;
//				preCreatTree = pre;
//				CreatTree = p;
//				CreatTreeDirection = Direction;
//			}
//		}
//		i++;
//	}
//	p->SetValue(value);
//	return true;
//}
//
//
//
//
//
//
//
//template<typename type>
//void BTree<type>::PreOrder()const
//{
//	BNode<type>* p = T;
//	LStack<BNode<type>*>S;
//	if(p)
//		S.push(p);
//	while (!S.empty())
//	{
//		p = S.top();
//		S.pop();
//		p->visit();
//		if (p->Getrchild() != nullptr)
//			S.push(p->Getrchild());
//		if (p->Getlchild() != nullptr)
//			S.push(p->Getlchild());
//	}
//}
//
//
//template<typename type>
//void BTree<type>::InOrder()const
//{
//	LStack<BNode<type>*>S;
//	BNode<type>* p = this->T;
//	if (p)
//		S.push(p);
//	bool IsPush = true;
//	while (!S.empty())
//	{
//		p = S.top();
//		if (IsPush&&p->Getlchild())
//		{
//			S.push(p->Getlchild());
//		}
//		else
//		{
//			IsPush = false;//出栈状态
//			S.pop();
//			p->visit();
//			if (p->Getrchild())//出栈元素只看右子树
//			{
//				S.push(p->Getrchild());
//				IsPush = true;
//			}
//		}
//	}
//}
//
////后序遍历
//template<typename type>
//void BTree<type>::PostOrder()const
//{
//	if (this->T == nullptr)
//		return;
//	LStack<BNode<type>*>S;
//	S.push(T);
//	BNode<type>* pre=nullptr;
//	while (!S.empty())
//	{
//		BNode<type>* p = S.top();//获取栈顶元素
//		if (p->Getlchild() && pre == nullptr)
//			S.push(p->Getlchild());
//		else if (p->Getrchild() && p->Getrchild() != pre)
//		{
//			S.push(p->Getrchild());
//			pre = nullptr;
//		}
//		else//visit
//		{
//			S.pop();
//			p->visit();
//			pre = p;
//		}
//	}
//}
//
////层次遍历
//template<typename type>
//void BTree<type>::LevelOrder()const
//{
//	LQueue<BNode<type>*>Q;
//	if (T == nullptr)return;
//	BNode<type>* p = T;
//	Q.push_back(p);
//	while (!Q.empty())//队列非空
//	{
//		p=Q.pop();
//		p->visit();
//		if (p->Getlchild())
//			Q.push_back(p->Getlchild());
//		if (p->Getrchild())
//			Q.push_back(p->Getrchild());
//	}
//}