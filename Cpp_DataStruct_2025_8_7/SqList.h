#pragma once
#include"Define.h"
//顺序表
typedef struct SqList
{
	ElemType data[MAXSIZE];
	unsigned int length;
};


/*--------------------------------------------------------------------*/


//初始化非动态内存管理的线性表
void InitSqList					(SqList& L);
//非动态内存管理的线性表进行插入元素
bool SqListInsert				(SqList& L,unsigned int i,ElemType e);
//非动态内存管理的线性表进行删除元素
bool SqListDelElem				(SqList& L,unsigned int i,ElemType &e);
//非动态内存管理的线性表进行按值查找
unsigned int SqListLocateElem	(SqList L, ElemType e);
//打印线性表
void PrintSqList				(SqList L);



/*--------------------------------------------------------------------*/





//				      留         白						  //









/*----------------------------------------------------------*/
//408考题(王道)

//03删除值为x的元素
bool Del_x(SqList& L, ElemType x);

//04删除值为从s到t的所有元素
bool DelElem_s_to_t(SqList &L,ElemType s,ElemType t);

//有序顺序性表去重
bool del_the_same(SqList& L);

//在有序递增顺序表当中找是否有元素x,如果没有则在保证有序的情况下插入顺序表
//如果有,则交换该元素与下一个元素的位置
bool Find_x_or_exchange(SqList& L, ElemType x);

//合并两个顺序表,并且返回一个新的顺序表
SqList CombineA_And_B(SqList A, SqList B);

//合并两个有序顺序表,返回一个新的有序顺序表
SqList CombineA_And_B_Sq(SqList A, SqList B);

//一个顺序表由两个顺序表构成,一个长度为m,另一个为n,元素为(a1,a2,...am)
// 另一个为(b1,b2,...bn),实现一个算法,使得(b1,b2,...bn)全部在(a1,a2,...am)
// 前面而且两个顺序表中元素相对位置不变
void Reverse_m_and_n(int arr[],int m,int n);


//T08一个递增有序的顺序表,使用最短时间在表中查找值为x的元素,如果找到了,与其后继元素位置互换
//如果没找到,则插入该元素同时保证顺序表仍旧递增
bool Find_x_or_Insert_x(SqList& L, ElemType x);

//T09三个有序递增数组中找共同元素
void From_A_B_C_Find_The_Same(int A[], int B[], int C[],int n);

//两个有序递增数组当中找中位数
int Find_Mid_Num(int A[], int B[], unsigned int length);

//T13
int Find_min_int(int arr[], int length);

//T14三个有序递增数组各取一个数形成三元组,求三元组的最小距离(存疑)
/*-----------------------------------------------------------*/