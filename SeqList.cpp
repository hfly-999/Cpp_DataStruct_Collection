#include"SeqList.h"
using namespace DSL;
//拷贝测试
void SeqListCopyTest()
{

	SeqList<double>arr;
	for (double i = 1.0; i <= 1024; i *= 2)
		arr.push_back(i);
	//arr1={1,2,4,8,16,32,64,128,256,512,1024};
	arr.Visit();
	SeqList<double>arr2 = arr;
	arr2.Visit();
	std::cout <<"arr size:" << arr.Getsize() << "\n";
	std::cout << "arr2 size:" << arr2.Getsize() << "\n";
}
//顺序表使用迭代器测试
void SeqListIteratorTest()
{
	SeqList<double>L;
	L.push_back(3.14);
	L.push_back(2.718);
	L.push_back(9.96);
	L.push_back(1.25);
	L.push_back(1e10);
	for (auto it = L.begin(); it != L.end(); it++)
		std::cout << *it << " ";
	//3.14 2.718 9.96 1.25 1e10
	std::cout << "\n";
}
//交换i与j下标的元素功能测试
void SeqListSwapTest()
{
	SeqList<double>L;
	L.push_back(3.14);
	L.push_back(2.718);
	L.push_back(9.96);
	L.push_back(1.25);
	L.push_back(1e10);
	L.Swap(0, 4);
	for (auto it = L.begin(); it != L.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n";
	//1e10 2.718 9.96 1.25 3.14
}
//顺序表各种插入功能的测试
void SeqListInsertTest()
{
	SeqList<void*>L;
	L.HeadInsert((void*)0x0012);
	L.push_back((void*)0x0012ff);
	L.Insert((void*)0x0012ee,1);
	L.Insert((void*)0x0012aa,1);

	for (auto it = L.begin(); it != L.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n";
	//0x0012,0x0012aa,0x0012ee,0x0012ff

}
//顺序表各种删除功能的测试
void SeqListDeleteTest()
{
	SeqList<int>L;
	for (int i = 1; i <=1024; i++)
	{
		L.push_back(i);
	}
	std::cout << L.DeleteHeadElement() << "\n";//1
	std::cout << L.DeleteTailElement() << "\n";//1024
	std::cout << L.Getsize() << "\n";//1022
	for (int i = 0; i < 10; i++)
		L.Delete(0);
	//12 13....1023
	for (auto it = L.begin(); it != L.end(); it++)
		std::cout << *it << " ";
	std::cout << "\n";
}

//拷贝构造函数测试
void SeqListCopyConstructorTest()
{
	SeqList<double>L;
	L.push_back(3.14);
	L.push_back(2.718);
	L.push_back(9.96);
	L.push_back(1.25);
	L.push_back(1e10);
	SeqList<double>newL = L;
	L.Visit();
	newL.Visit();
}
//顺序表表赋值功能测试
void SeqListEqualOverLoadTest()
{
	SeqList<double>L;
	L.push_back(3.14);
	L.push_back(2.718);
	L.push_back(9.96);
	L.push_back(1.25);
	L.push_back(1e10);
	SeqList<double>NewL;
	NewL = L;
	L.Visit();
	NewL.Visit();
	//3.14
	//2.718
	//9.96
	//1.25
	//1e10
}
