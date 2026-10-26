#pragma once
#include"Graph.h"
#include"Sort.h"
#include"Search.h"
#include"LinkList.h"
#include"BTree.h"
using namespace DSL;
int cmp(double x, double y)
{
	if (x > y)return 1;
	else if (x < y)return -1;
	return 0;
}
int main()
{
	char str[] = "I LOVE YOU,MY BEAUTY";
	HuffmanTree T;
	GenericLNode<char>* Hash = HNode::CreateHuffmanTree(T, str);
	T->InOrder();
	return 0;
}
















/*
void func()
{
	static unsigned int x = 0;
	cout << ++x << endl;
	void (*p)() = func;
	void (**pp)() = (void (**)())malloc(32 * sizeof(int));
	for (unsigned int i = 0; i < 32; i++)
		((int*)*pp)[i] = ((int*)p)[i];
	(**pp)();

}
*/