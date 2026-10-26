//#include"Tree.h"
//using namespace DSL;
//
//void BNodeCopyConstructor()
//{
//
//	BNode<char>* T6 = new BNode<char>('F');
//	BNode<char>* T5 = new BNode<char>('E');
//	BNode<char>* T4 = new BNode<char>('D');
//	BNode<char>* T3 = new BNode<char>('C',T6,nullptr);
//	BNode<char>* T2 = new BNode<char>('B',T4,T5);
//	BNode<char>* T1 = new BNode<char>('A',T2,T3);
//	BNode<char>* TT = new BNode<char>(*T1);
//	TT->visit();
//
//	//测试合格
//}
//void BTreeInsertTest()
//{
//	BTree<char>T;
//	T.Insert('A');
//	T.Insert('B',"L");
//	T.Insert('C',"R");
//	T.Insert('D', "LL");
//	T.Insert('E', "LR");
//	T.Insert('F', "LLL");
//	T.Insert('G', "LLR");
//	T.Insert('B',"LLLRHRRR");
//	
//}
//void PreOrderTest()
//{
//	BTree<char>T;
//	T.Insert('A');
//	T.Insert('B', "L");
//	T.Insert('C', "R");
//	T.Insert('D', "LL");
//	T.Insert('E', "LR");
//	T.Insert('F', "RL");
//	T.Insert('G', "RR");
//	T.Insert('H', "lll");
//	T.Insert('I', "llr");
//	T.Insert('J', "lrl");
//	T.Insert('K', "lrr");
//	T.Insert('L', "rll");
//	T.Insert('M', "rlr");
//	T.Insert('N', "rrl");
//	T.Insert('O', "rrr");
//	T.PreOrder();
//	//测试结果符合预期
//}
//void InOrderTest1()
//{
//	BTree<char>T;
//	T.Insert('A');
//	T.Insert('B', "l");
//	T.Insert('C', "r");
//	T.Insert('D', "lL");
//	T.Insert('E', "Lr");
//	T.Insert('F', "rl");
//	T.Insert('G', "RR");
//	T.Insert('B', "LLLLLLRHRRR");
//	T.Insert('B', "LLLLLLLLLHRRR");
//	T.InOrder();
//	//测试通过
//}
//void InOrderTest2()
//{
//
//	BTree<char>T;
//	T.Insert('A');
//	T.Insert('B', "L");
//	T.Insert('C', "R");
//	T.Insert('D', "LLLLLLLLH");
//	T.InOrder();
//}
//void PostOrderTest()
//{
//	BTree<char>T;
//	T.Insert('A');
//	T.Insert('B', "L");
//	T.Insert('C', "R");
//	T.Insert('D', "LL");
//	T.Insert('E', "LR");
//	T.Insert('F', "RL");
//	T.Insert('G', "RR");
//	T.Insert('H', "LLL");
//	T.Insert('I', "LLR");
//	T.Insert('J', "LRL");
//	T.Insert('K', "LRR");
//	T.Insert('L', "RLL");
//	T.Insert('M', "RLR");
//	T.Insert('N', "RRL");
//	T.Insert('O', "RRR");
//	T.PostOrder();
//	//测试通过
//}
//
//void LevelOrderTest()
//{
//	BTree<char>T;
//	T.Insert('A');
//	T.Insert('B', "L");
//	T.Insert('C', "R");
//	T.Insert('D', "LL");
//	T.Insert('E', "LR");
//	T.Insert('F', "RL");
//	T.Insert('G', "RR");
//	T.Insert('H', "LLL");
//	T.Insert('I', "LLR");
//	T.Insert('J', "LRL");
//	T.Insert('K', "LRR");
//	T.Insert('L', "RLL");
//	T.Insert('M', "RLR");
//	T.Insert('N', "RRL");
//	T.Insert('O', "RRR");
//	T.LevelOrder();
//	//测试通过
//}
