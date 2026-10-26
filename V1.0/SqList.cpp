#include"SqList.h"

void InitSqList(SqList& L)
{
	L.length = 0;
}

bool SqListInsert(SqList& L, unsigned int i, ElemType e)
{
	if (i > MAXSIZE)return false;
	unsigned int j = L.length;
	for (j; j > i-1; j--)
	{
		L.data[j] = L.data[j - 1];
		
	}
	L.data[i-1] = e;
	L.length++;
	return true;
}

void PrintSqList(SqList L)
{
	unsigned int i = 0;
	for (i; i < L.length; i++)
		printf("%d ", L.data[i]);
	printf("\n");
}

bool SqListDelElem(SqList& L, unsigned int i, ElemType& e)
{
	if (i > L.length)return false;
	unsigned int j = i-1;
	e = L.data[j];
	for (j; j < L.length; j++)
	{
		L.data[j] = L.data[j + 1];
	}
	L.length--;
	return true;
}


unsigned int SqListLocateElem(SqList L, ElemType e)
{
	unsigned int i = 0;
	for (i; i < L.length; i++)
		if (L.data[i] == e)return i + 1;
	return 0;//没找到 
}

bool Del_x(SqList& L, ElemType x)
{
	if (L.length == 0)return false;
	int i = 0, j = L.length - 1;
	while (i < j)
	{
		if (L.data[i] == x)
		{
			L.data[i] = L.data[j];
			j--;
			continue;
		}
		i++;
	}
	L.length = j + 1;
	return true;
}

bool DelElem_s_to_t(SqList& L, ElemType s, ElemType t)
{
	if (s >= t || L.length == 0)return false;
	int i, k = 0;
	for (i = 0; i < L.length; i++)
		if (L.data[i] <= s || L.data[i] >= t)
			L.data[k++] = L.data[i];
	L.length = k;
	return true;
}

bool del_the_same(SqList& L)
{
	// 1 1 1 2 2 2 2 3 4 4 4 5 6 7 7 8 8 9
	//1 2 3 4 5 6 7 8 9
	int i=0, j;
	for (j = 0; j < L.length; j++)
	{
		if (L.data[i] != L.data[j])
		{
			i++;
			L.data[i] = L.data[j];
		}
	}
	L.length = i + 1;
	return true;
}

SqList CombineA_And_B(SqList A, SqList B)
{
	SqList ret;
	ret.length = 0;
	int i ;
	for (i = 0; i < A.length; i++)ret.data[ret.length++] = A.data[i];
	for (i = 0; i < B.length; i++)ret.data[ret.length++] = B.data[i];
	return ret;
}

SqList CombineA_And_B_Sq(SqList A, SqList B)
{
	SqList ret;
	ret.length = 0;
	int i = 0, j = 0;
	while (i < A.length && j < B.length)
	{
		if (A.data[i] <= B.data[j])ret.data[ret.length++] = A.data[i++];
		else ret.data[ret.length++] = B.data[j++];
	}
	while (i < A.length)ret.data[ret.length++] = A.data[i++];
	while (j < B.length)ret.data[ret.length++] = B.data[j++];
	return ret;
}

bool Find_x_or_Insert_x(SqList& L, ElemType x)
{
	if (L.length == 0)
	{
		L.data[L.length++] = x;
		return false;
	}
	int left = 0, right = L.length, mid = (left + right) / 2;
	while(L.data[left]!=x&&L.data[mid]!=x)
	{ 
		if (left == mid)
		{
			int i;
			for (i = L.length; i > mid; i--)
				L.data[i] = L.data[i - 1];
			L.length++;
			L.data[mid] = x;
			return false;
		}
		if (x < L.data[mid])
		{
			right = mid;
		}
		else
		{
			left = mid;
		}
		mid = (left + right) / 2;
	}
	if (L.data[left] == x)
	{
		ElemType tmp = L.data[left];
		L.data[left] = L.data[left + 1];
		L.data[left + 1] = tmp;
	}
	else
	{
		ElemType tmp = L.data[mid];
		L.data[mid] = L.data[mid + 1];
		L.data[mid + 1] = tmp;
	}
	
	return true;
}

void From_A_B_C_Find_The_Same(int A[], int B[], int C[], int n)
{
	int max = A[0], min = B[0];
	int i;
	for (i = 0; i < n; i++)
	{
		max = max < A[i] ? A[i] : max;
		max = max < B[i] ? B[i] : max;
		max = max < C[i] ? C[i] : max;
		min = min > A[i] ? A[i] : min;
		min = min > B[i] ? B[i] : min;
		min = min > C[i] ? C[i] : min;
	}
	int* hash = (int*)calloc(max - min + 1, sizeof(int));
	for (i = 0; i < n; i++)
	{
		hash[A[i] - min]++;
		hash[B[i] - min]++;
		hash[C[i] - min]++;
	}
	for (i = 0; i < max - min + 1; i++)
		if (hash[i] == 3)
			printf("%d ", i + min);
}

void Reverse_m_and_n(int arr[], int m, int n)
{
	int left = 0, right = m - 1,tmp;
	while (left < right)
	{
		tmp = arr[left];
		arr[left] = arr[right];
		arr[right] = tmp;
		left++;
		right--;
	}
	left = m;
	right = m + n - 1;
	while (left < right)
	{
		tmp = arr[left];
		arr[left] = arr[right];
		arr[right] = tmp;
		left++;
		right--;
	}
	left = 0;
	right = m + n - 1;
	while (left < right)
	{
		tmp = arr[left];
		arr[left] = arr[right];
		arr[right] = tmp;
		left++;
		right--;
	}
}

int Find_Mid_Num(int A[], int B[], unsigned int length)
{
	int i = 0, j = 0;
	while (i + j + 1 < length)
	{
		if (A[i] <= B[j])i++;
		else j++;
	}
	if (A[i] < B[j])return A[i];
	else return B[j];
}

int Find_min_int(int arr[], int length)
{
	int ret = 1;
	int i;
	for (i = 0; i < length; i++)
		if (arr[i] == ret)ret++;
	for (i = length - 1; i != -1; i--)
		if (arr[i] == ret)ret++;
	return ret;
		
}

bool Find_x_or_exchange(SqList& L, ElemType x)
{
	if (L.length == 0)
	{
		L.data[L.length++] = x;
		return false;
	}
	if (L.length == 1)
	{
		if (L.data[0] == x)return true;
		else if (L.data[0] < x)
		{
			L.data[L.length++] = x;
			return false;
		}
		else
		{
			L.data[L.length++] = L.data[0];
			L.data[0] = x;
		}
	}
	if (x < L.data[0])
	{
		int i;
		for (i = L.length; i > 0; i--)L.data[i] = L.data[i - 1];
		L.data[0] = x;
		L.length++;
		return false;
	}
	else if (x > L.data[L.length - 1])
	{
		L.data[L.length++] = x;
		return false;
	}
		
	
	int left = 0, right = L.length - 1, mid = (left + right) / 2;
	while (L.data[mid]!=x)
	{
		if (left + 1 == right)//在索引内的元素只有两个
		{
			if (L.data[right] == x)
			{
				return true;
			}
			else//没找到
			{
				int i;
				for (i = L.length; i > right; i--)
				{
					L.data[i] = L.data[i - 1];
				}
				L.length++;
				L.data[right] = x;
				return false;
			}
		}
		if (x < L.data[mid])
		{
			right = mid;
			mid = (left + right) / 2;
		}
		else
		{
			left = mid;
			mid = (left + right) / 2;
		}
	}
	ElemType tmp = L.data[mid];
	L.data[mid] = L.data[mid + 1];
	L.data[mid + 1] = tmp;
	return true;
}











