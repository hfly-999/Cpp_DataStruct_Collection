
#include"Sort.h"
namespace DSL
{
//--------------------------------------------------------------------------//
/*											
*		DataStruct-GenericSqList(·ºÐÍË³Ðò±í)	
*											
*		Created by HFLY						
*											
*				---time:2026.6.1			
*											
*/	
//--------------------------------------------------------------------------//
	template<typename type>
	GenericSqList<type>::GenericSqList()
	{
		Data = new type[DEFAULT_SQLIST_SIZE];
		length = 0;//
		MaxLength = DEFAULT_SQLIST_SIZE - 1;//
	}


	template<typename type>
	GenericSqList<type>::~GenericSqList()
	{
		delete Data;
	}


	template<typename type>
	bool GenericSqList<type>::Exchange(unsigned int x, unsigned int y)
	{
		if (x<1 || x>this->length)return false;
		if (y<1 || y>this->length)return false;
		type tmp = this->Data[x];
		this->Data[x] = this->Data[y];
		this->Data[y] = tmp;
		return true;
	}


	template<typename type>
	bool GenericSqList<type>::IsFull()
	{
		if (length == MaxLength)return true;
		return false;
	}


	template<typename type>
	bool GenericSqList<type>::Insert(type e, unsigned int pos)
	{
		if (IsFull() == true)return false;
		if (pos >= DEFAULT_SQLIST_SIZE || pos > length + 1 || pos = 0)return false;
		for (unsigned int i = length + 1; i > pos; i++)
			Data[i] = Data[i - 1];
		this->length++;
		Data[pos] = e;
		return true;
	}


	template<typename type>
	bool GenericSqList<type>::Insert(type e)
	{
		if (IsFull() == true)return false;
		Data[++length] = e;
		return true;
	}


	template<typename type>
	bool GenericSqList<type>::IsEmpty()
	{
		if (this->length == 0)return true;
		return false;
	}


	template<typename type>
	int GenericSqList<type>::GetLength()
	{
		return this->length;
	}
}