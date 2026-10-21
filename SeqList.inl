#include"SeqList.h"
using namespace DSL;






//无参构造
template<typename type>
SeqList<type>::SeqList():
	size(0),
	Capacity(GetCapacity()),
	Data(new type[Capacity]){

}


//拷贝构造函数
template<typename type>
SeqList<type>::SeqList(const SeqList& obj) :
	size(obj.size),
	Capacity(obj.Capacity),
	Data(new type[Capacity]){
	for (size_t i = 0; i < obj.size; i++)//深拷贝
		Data[i] = obj.Data[i];
}

//无参析构
template<typename type>
SeqList<type>::~SeqList()
{
	//std::cout << "删除了顺序表类型" << std::endl;
	delete []Data;
}



//赋值运算符重载
template<typename type>
SeqList<type>& SeqList<type>::operator=(const SeqList<type>& that)
{
	delete this->Data;//释放旧有的内存空间
	size = that.size;//复制大小
	Capacity = GetCapacity();//计算容量
	Data = new type[Capacity];//重新申请内存
	for (size_t i = 0; i < size; i++)//复制内容
		this->Data[i] = that.Data[i];
	return *this;//
}

//[]重载
template<typename type>
type& SeqList<type>::operator[](size_t i)
{
	if (i >= size)exit(3);
	return Data[i];
}



//获取起始指针
template<typename type>
type* SeqList<type>::begin() const
{
	return Data;
}




//获取尾部指针
template<typename type>
type* SeqList<type>::end() const
{
	return Data + size;
}






//插入到下标为i的地方
template<typename type>
void SeqList<type>::Insert(type element, size_t position)
{
	if (position >= Capacity)//插入位置在容量之后
	{
		AllocMoreMemory(position + 1);//先扩容
		size = position + 1;
	}
	else if (size == Capacity)//插入位置在容量之前,并且需要扩容
	{
		AllocMoreMemory();//
		size++;
	}
	else size++;
	for (size_t i = size-1; i > position; i--)
		Data[i] = Data[i - 1];//元素后移
	Data[position] = element;
}
//头插
template<typename type>
void SeqList<type>::HeadInsert(type element)
{
	Insert(element, 0);
}
//尾插
template<typename type>
void SeqList<type>::push_back(type element)
{
	Insert(element, size);
}


//删除下标为i的元素并且返回val值
template<typename type>
type SeqList<type>::Delete(size_t position)
{
	if (position > size)return type{};//如果删除位置不合法直接返回0
	else
	{
		type ret = Data[position];//记录返回值
		for (size_t i = position; i < size; i++)
		{
			Data[i] = Data[i + 1];//挪动元素
		}
		size--;//长度减少
		if (size == Capacity / 2)
			AllocLessMemory();//动态减容
		return ret;//返回
	}
}
//删除尾部元素并返回val值
template<typename type>
type SeqList<type>::DeleteTailElement()
{
	return Delete(size - (size_t)(1));//删除尾部元素
}
//删除头部元素并返回val值
template<typename type>
type SeqList<type>::DeleteHeadElement()
{
	return Delete(0);//删除首元素
}
//交换i与j下标的元素
template<typename type>
bool SeqList<type>::Swap(size_t i, size_t j)
{
	if (i >= size || j >= size)return false;
	type tmp = Data[i];
	Data[i] = Data[j];
	Data[j] = tmp;
	return true;
}
//查找下标为i的元素
template<typename type>
type SeqList<type>::Find(size_t i)const
{
	if (i >= size)return type{};
	return Data[i];
}


//使用迭代器遍历顺序表
template<typename type>
void SeqList<type>::Visit()const
{
	for (auto it = this->begin(); it != this->end(); it++)
		std::cout << it << ":" << *it << std::endl;
	std::cout << "\n";
	
}

//获取顺序表长度
template<typename type>
size_t SeqList<type>::Getsize() const
{
	return this->size;
}
template<typename type>
size_t SeqList<type>::GetCapacity()const
{
	return size + size / 2 + 1;
}
template<typename type>
void SeqList<type>::AllocMoreMemory(size_t NewCapacity)
{
	if (NewCapacity == 0)				//按常规方法扩容
		Capacity = Capacity + Capacity / 2 + 1;
	else 
		Capacity = NewCapacity;			//按需扩容
	type* OldMemory = Data;
	Data = new type[Capacity];
	for (size_t i = 0; i < size; i++)
		Data[i] = OldMemory[i];
	for (size_t i = size; i < Capacity; i++)
		Data[i] = type{};				//初始化未使用的内存,防止魔法数0XCDCDCDCD的出现
	delete[] OldMemory;
}
template<typename type>
void SeqList<type>::AllocLessMemory(size_t NewCapacity)
{
	if (NewCapacity == 0)//按常规方法缩容
		Capacity = Capacity / 2 + 1;
	else 
		Capacity = NewCapacity;//按需缩容
	type* OldMemory = Data;
	Data = new type[Capacity];
	for (size_t i = 0; i < size; i++)
		Data[i] = OldMemory[i];
	for (size_t i = size; i < Capacity; i++)
		Data[i] = type{};//初始化未使用的内存,防止魔法数0XCDCDCDCD的出现
	delete[] OldMemory;
}




