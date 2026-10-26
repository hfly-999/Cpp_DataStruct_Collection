
#include"Sort.h"

namespace DSL
{
/*											//
*		DataStruct-HeapSqList(泛型堆)		//
*											//
*		Created by HFLY						//
*											//
*				---time:2026.6.1			//
*											//
*/											//
	template<typename type>
	GenericHeap<type>::GenericHeap(int cmp(type A, type B))
	{
		this->cmp = cmp;
		pattern = Small;
	}


	template<typename type>
	GenericHeap<type>::GenericHeap(int cmp(type A, type B), ENUM_HEAPPATTERN pattern)
	{
		this->cmp = cmp;
		this->pattern = pattern;
	}


	template<typename type>
	GenericHeap<type>::~GenericHeap() {}


	template<typename type>
	bool GenericHeap<type>::Push(type e)
	{
		if (this->IsFull() == true)return false;
		GenericSqList<type>::Insert(e);
		int p = this->length;
		while (p != 1)
		{
			if ((int)this->pattern * cmp(this->Data[p], this->Data[p / 2]) < 0)
			{
				this->Data[0] = this->Data[p];
				this->Data[p] = this->Data[p / 2];
				this->Data[p / 2] = this->Data[0];
				p /= 2;
			}
			else break;
		}
		return true;

	}


	template<typename type>
	bool GenericHeap<type>::Pop(type& e)
	{
		if (this->IsEmpty() == true)return false;
		e = this->Data[1];//返回值
		this->Data[1] = this->Data[this->length--];//把堆尾元素放到堆丁
		unsigned int p = 1;//从堆顶开始
		while (p <= this->length / 2)//不是叶子节点
		{
			if ((2 * p + 1) <= this->length)//有右子树
			{
				if (
					(int)this->pattern * cmp(this->Data[p], this->Data[2 * p]) > 0
					||
					(int)this->pattern * cmp(this->Data[p], this->Data[2 * p + 1]) > 0
					)//可能要和左右子树交换
				{
					if ((int)this->pattern * cmp(this->Data[2 * p], this->Data[2 * p + 1]) < 0)//要左边换，左边小
					{
						this->Exchange(p, 2 * p);
						p *= 2;

					}
					else //要和右边换
					{
						this->Exchange(p, 2 * p + 1);
						p = (2 * p + 1);
					}
				}
				else break;//不需要再进行交换了
			}
			else //无右子树
			{
				if (
					(int)this->pattern * cmp(this->Data[p], this->Data[2 * p]) > 0
					)//要左边换
				{
					this->Exchange(p, 2 * p);
				}
				break;
			}

		}
		return true;
	}


	template<typename type>
	type GenericHeap<type>::Pop()
	{
		type ret = (type)0x0000;
		this->Pop(ret);
		return ret;
	}
}
