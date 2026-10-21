#include"LinkList.h"
using namespace DSL;

//void LinkListHeadInsertTest()
//{
//	LinkList<double>L;
//	L.HeadInsert(3.14);
//	L.HeadInsert(2.718);
//	L.HeadInsert(3.996);
//	L.HeadInsert(4.111);
//	L.HeadInsert(1024);
//	L.HeadInsert(65536.8125);
//	//L={65536.8125,1024,4.111,3.996,2.718,3.14};
//	L.Visit();
//}
//void LinkListpush_backTest()
//{
//	LinkList<double>L;
//	L.push_back(1.000);
//	L.push_back(2.718);
//	L.push_back(3.14159);
//	L.push_back(6.666);
//	L.push_back(9.999);
//	L.push_back(65536.8125);
//	//L={1.000,2.718,3.14159,6.666,9.999,65536.8125};
//	L.Visit();
//}
//
//void LinkListHeadDeleteTest()
//{
//	LinkList<double>L;
//	L.push_back(1.000);
//	L.push_back(2.718);
//	L.push_back(3.14159);
//	L.push_back(6.666);
//	L.push_back(9.999);
//	L.push_back(65536.8125);
//	//L={1.000,2.718,3.14159,6.666,9.999,65536.8125};
//	L.HeadDelete();
//	L.HeadDelete();
//
//	//L={3.14159,6.666,9.999,65536.8125};
//	L.Visit();
//
//
//}
//
//void LinkListTailDeleteTest()
//{
//	LinkList<double>L;
//	L.push_back(1.000);
//	L.push_back(2.718);
//	L.push_back(3.14159);
//	L.push_back(6.666);
//	L.push_back(9.999);
//	L.push_back(65536.8125);
//	//L={1.000,2.718,3.14159,6.666,9.999,65536.8125};
//	L.TailDelete();
//	L.TailDelete();
//
//	//L={1.000,2.718,3.14159,6.666};
//	L.Visit();
//}
//void LinkListCopyConstructorTest()
//{
//	LinkList<double>L;
//	L.push_back(1.000);
//	L.push_back(2.718);
//	L.push_back(3.14159);
//	L.push_back(6.666);
//	L.push_back(9.999);
//	L.push_back(65536.8125);
//	LinkList<double>newL = L;//拷贝构造函数测试
//	L.Visit();
//	newL.Visit();
//}
//void LinkListEqualTest()
//{
//	LinkList<double>L;
//	L.push_back(1.000);
//	L.push_back(2.718);
//	L.push_back(3.14159);
//	L.push_back(6.666);
//	L.push_back(9.999);
//	L.push_back(65536.8125);
//	LinkList<double>newL;
//	newL = L;//赋值拷贝测试
//	L.Visit();
//	newL.Visit();
//}
//
//void LinkListIsEqualTest()
//{
//	LinkList<double>L;
//	L.push_back(1.000);
//	L.push_back(2.0);
//	L.push_back(4.0);
//	L.push_back(8.0);
//	L.push_back(16.0);
//	L.push_back(32.0);
//	LinkList<double>NewL;
//	NewL.push_back(1.000);
//	NewL.push_back(2.0);
//	NewL.push_back(4.0);
//	NewL.push_back(8.0);
//	NewL.push_back(16.0);
//	NewL.push_back(32.0);
//	if (NewL == L)
//		std::cout << "equal\n";
//	else std::cout << "unequal\n";
//	//"equal"
//}
