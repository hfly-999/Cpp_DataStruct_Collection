#include"Sort.h"

bool SeqInsertSort(SqList& L)
{
	if (L.length == 0)return false;
	for (int i = 2; i <= L.length; i++)//遍历2~n个元素
	{
		if (L.r[i].key < L.r[i - 1].key)//当当前元素的key值小于前一个元素的key值的时候
		{
			L.r[0] = L.r[i];//将当前元素位置保存到L.r[0]处
			int j = i - 1;
			while (L.r[j].key > L.r[0].key)//当j元素的key值大于当前元素的key值的时候
			{
				L.r[j + 1] = L.r[j];
				j--;
			}
			L.r[j + 1] = L.r[0];//将L.r[0]赋值给不大于L.r[0]的下一个元素
		}
	}
	return true;
}
bool BinaryInsertSort(SqList& L)
{
	if (L.length == 0)return false;
	for (int i = 2; i <= L.length; i++)
	{
		int low = 1;
		int high = i - 1;
		int mid = (low + high) / 2;
		L.r[0] = L.r[i];
		while (low <= high)
		{
			if (L.r[0].key < L.r[mid].key)//i在mid的左边
				high = mid - 1;
			else //i在mid的右边
				low = mid + 1;
			mid = (low + high) / 2;//更新mid的值
		}//找到插入的位置,high+1 //low
		for (int j = i; j >low; j--)
		{
			L.r[j] = L.r[j-1];
		} 
		L.r[low] = L.r[0];
	}
	return true;
}

bool Insert(SqList& L, KeyType key)
{
	if (L.length == MAXSIZE+1)return false;
	L.r[L.length+1].key = key;
	L.length++;
	return true;
}

void Print(SqList L)
{
	for (int i = 1; i <= L.length; i++)
		printf("%d ", L.r[i].key);
	printf("\n");

}

void Init(SqList& L)
{
	L.length = 0;
}

void ShellSort(SqList& L, int dlta[], int t)
{
	for (int i = 0; i < t; i++)
		ShellInsert(L, dlta);
}


void ShellInsert	(SqList& L, int dlta[])
{

}


void BubbleSort		(SqList& L)
{
	if (L.length == 0 || L.length == 1)return;
	for (int i = 1; i <= L.length; i++)
	{
		int count = 0;
		for (int j = 1; j <= L.length - i; j++)
		{
			if (L.r[j].key > L.r[j+1].key)
			{
				L.r[0] = L.r[j+1];
				L.r[j+1] = L.r[j];
				L.r[j] = L.r[0];
				count++;
			}	
		}
		if (count == 0)break;
	}

		
	return;
}



void qsort			(SqList& L, int low, int high)
{
	if (low >= high)return;
	int pos = low;//初始值的位置
	int tag = 1;//查找成功的次数
	while (tag!=0)
	{
		tag = 0;
		int i = high;//从右边开始找
		while (i != pos)
		{
			if (L.r[i].key < L.r[pos].key)//找到了一个小的
			{
				L.r[0] = L.r[i];
				L.r[i] = L.r[pos];
				L.r[pos] = L.r[0];
				pos = i;
				tag++;
				break;
			}
			i--;
		}
		pos = i;
		i = low;//从左边开始找
		while (i!=pos)
		{
			if (L.r[i].key >= L.r[pos].key)
			{
				L.r[0] = L.r[i];
				L.r[i] = L.r[pos];
				L.r[pos] = L.r[0];
				pos = i;
				tag++;
				break;
			}
			i++;
		}	
	}
	qsort(L, low, pos - 1);
	qsort(L, pos + 1, high);
}

void Init(Heap& H)
{
	H.length = 0;
	for (int i = 0; i < MAXSIZE; i++)
		H.data[i] = MAX_INT_16;
}

bool Insert(Heap& H,KeyType key)
{
	if (H.length == MAX_INT_16)return false;
	H.data[++H.length] = key;
	return true;
}


KeyType Output(Heap& H)
{
	KeyType ret = H.data[1];//记录堆顶元素
	H.data[1] = H.data[H.length];//堆顶元素等于最后一个元素
	//删除最后一个元素
	H.data[H.length] = MAX_INT_16;
	H.length--;
	Regulate(H, 1);//调整
	return ret;
}

void Regulate(Heap& H, int pos)
{
	if (H.data[2 * pos] == MAX_INT_16 && H.data[2 * pos + 1] == MAX_INT_16)return;
	if (H.data[2 * pos + 1] == MAX_INT_16)//如果它没有右孩子
	{
		if (H.data[2 * pos] < H.data[pos])
		{
			H.data[0] = H.data[2 * pos];
			H.data[2 * pos] = H.data[pos];
			H.data[pos] = H.data[0];
			Regulate(H, 2 * pos);
		}
	}
	else if (H.data[pos] > H.data[2 * pos] || H.data[pos] > H.data[2 * pos + 1])
	{
		if (H.data[2 * pos] < H.data[2 * pos + 1])//如果左边的小
		{
			H.data[0] = H.data[2 * pos];
			H.data[2 * pos] = H.data[pos];
			H.data[pos] = H.data[0];
			Regulate(H, 2 * pos);
		}
		else//如果右边的小
		{
			H.data[0] = H.data[2 * pos + 1];
			H.data[2 * pos + 1] = H.data[pos];
			H.data[pos] = H.data[0];
			Regulate(H, 2 * pos+1);
		}
	}

}

void HeapSort(Heap& H)
{
	for(int i = H.length / 2; i > 0; i--)
		Regulate(H, i);
}




bool InsertInHeap	(Heap& H, KeyType key)
{
	if (H.length == MAX_INT_16 - 1)return false;
	H.data[++H.length] = key;
	int pos = H.length;
	while (H.data[pos] < H.data[pos / 2]&&pos!=1)
	{
		H.data[0] = H.data[pos];
		H.data[pos] = H.data[pos / 2];
		H.data[pos / 2] = H.data[0];
		pos = pos / 2;
	}
	return true;
}//时间复杂度(O(logn))

void MergeSort(SqList& L,int low,int high)
{
	if (low == high)return;
	if (high - low == 1)
	{
		if (L.r[high].key < L.r[low].key)
		{
			L.r[0] = L.r[low];
			L.r[low] = L.r[high];
			L.r[high] = L.r[0];
		}
		return;
	}
	int mid = (low + high) / 2;
	//
	int i = low;
	int j = mid + 1;
	MergeSort(L, low, mid);
	MergeSort(L, mid + 1, high);
	RedType* array = (RedType*)malloc((high - low + 1) * sizeof(RedType));
	int k = 0;//array ptr
	while (i != mid + 1 && j != high + 1)
	{
		if (L.r[i].key < L.r[j].key)//右边大
		{
			array[k++] = L.r[i++];
		}
		else if (L.r[i].key > L.r[j].key)//左边大
		{
			array[k++] = L.r[j++];
		}
		else//一样大
		{
			array[k++] = L.r[i++];
			array[k++] = L.r[j++];
		}
	}
	while(i != mid + 1)array[k++] = L.r[i++];
	while(j != high + 1)array[k++] = L.r[j++];
	for (i = 0; i < k; i++)
		L.r[low + i] = array[i];
	

}


void BucketSort(SqList& L)
{

}


void CountSort		(int A[], int length)
{
	int* count = (int*)malloc(length * sizeof(int));
	int* B = (int*)malloc(length * sizeof(int));
	if (count==NULL || B==NULL)return;
	for (int i = 0; i < length; i++)count[i] = 0;//count
	for (int i = 0; i < length - 1; i++)
		for (int j = i+1; j < length; j++)
			if (A[i] <A[j])count[j]++;
			else count[i]++;
	for (int i = 0; i < length; i++)
		B[count[i]] = A[i];
	for (int i = 0; i < length; i++)
		A[i] = B[i];
	free(count);
	free(B);
}
































































