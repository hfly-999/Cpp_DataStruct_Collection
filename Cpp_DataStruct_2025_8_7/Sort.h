#pragma once
#include"Define.h"

typedef struct
{
	KeyType		key;
}RedType;//Record Type

typedef struct
{
	RedType		r[MAXSIZE + 1];
	int			length;//顺序表表长
}SqList;

typedef struct
{
	KeyType		data[MAXSIZE];
	int			length;
}Heap;

typedef struct BucketNode//桶节点
{
	RedType data;
	BucketNode* next;
}BucketNode;



/*------------------------Sort.h-------------------------*/
//基础算法
//
bool Insert			(SqList& L, KeyType key);
//顺序表的初始化
void Init			(SqList& L);
//顺序插入排序
bool SeqInsertSort	(SqList& L);
//折半插入排序
bool BinaryInsertSort(SqList& L);
//希尔排序
void ShellSort		(SqList& L,int dlta[],int t);
//希尔插入
void ShellInsert	(SqList& L, int dlta[]);
//冒泡排序
void BubbleSort		(SqList& L);
//快排2.0
void qsort			(SqList& L, int low, int high);
//打印
void Print			(SqList  L);
/*------------------------Sort.h-------------------------*/
//堆的初始化
void Init			(Heap& H);
//输出
KeyType Output		(Heap& H);
//调整
void Regulate		(Heap& H, int pos);
//堆排序
void HeapSort		(Heap& H);
//堆的无序插入(插入最后一个位置之后,不再做任何调整)
bool Insert			(Heap& H, KeyType key);
//堆有序之后进行插入(在一个有序的小顶堆当中进行插入,并且使得插入之后的堆仍旧有序)
bool InsertInHeap	(Heap& H, KeyType key);
/*------------------------Sort.h-------------------------*/
//2路归并排序
void MergeSort		(SqList& L,int low,int high);

/*------------------------Sort.h-------------------------*/
//桶排序
void BucketSort		(SqList& L);
/*------------------------Sort.h-------------------------*/
//计数排序
void CountSort		(int A[],int length);