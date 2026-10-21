#include"String.h"

namespace DSL
{
	void BFTest1()
	{
		String str = "I LOVE THE WORLD.SO,I WANT TO DEVOTE MYSELF TO THE WORLD";  

		String son = "WANT";
		std::cout<<str.BF(son)<<"\n";
		//23
	}
	void KMPTest1()
	{
		String str = "I LOVE THE WORLD.SO,I WANT TO DEVOTE MYSELF TO THE WORLD";
		String son = "WANT";
		std::cout << str.KMP(son) << "\n";
		//23
	}
}


namespace DSL
{
	/*String::String():
		size(0),
		capacity((size_t)(size + size / 2) + 1),
		Data(new char[capacity])
	{
		Data[size] = '\0';
	}*/
	String::String(const char* str) :
		size(strlen(str)),
		capacity((size_t)(size + size / 2) + 1),
		Data(new char[capacity])
	{
		strcopy(Data, str);
		Data[size] = '\0';
	}
	String::String(const std::string& str) :
		size(str.size()),
		capacity((size_t)(size + size / 2) + 1),
		Data(new char[capacity])
	{
		
		strcopy(Data, str);
		Data[size] = '\0';
	}
	String::String(const String& obj) :
		size(obj.size),
		capacity(obj.capacity),
		Data(new char[capacity])
	{
	
		strcopy(Data, (const char*)obj.Data);
		Data[size] = '\0';
	}
	String::~String()
	{
		delete[] Data;
	}
	//获取字符串的next数组
	size_t* String::Getnext()const
	{
		size_t i = 0;
		size_t count = 0;//最小公共前后缀
		size_t* next = new size_t[size];
		next[i++] = 0;
		while (i < size)
		{
			if (Data[i] == Data[count])
				next[i++] = ++count;
			else if (count == 0)
				next[i++] = count;
			else count = next[count - 1];
		}//PM
		for (i = size - 1; i > 0; i--)
			next[i] = next[i - 1];

		//print
		//for (i = 0; i < size; i++)
		//	std::cout << next[i] << " ";
		//std::cout <<std:: endl;

		return next;
	}
	size_t* String::Getnextval()const
	{

		size_t* nextval = Getnext();
		for (size_t i = 0; i < size; i++)
			while (nextval[i] != 0 && Data[i] == Data[nextval[i]])
				nextval[i] = nextval[nextval[i]];

		/*for (size_t i = 0; i < size; i++)
			std::cout << nextval[i] << " ";
		std::cout << std::endl;*/

		return nextval;
	}
	size_t String::Getsize()const
	{
		return this->size;
	}

	size_t String::GetCapacity()const
	{
		return this->capacity;
	}

	size_t String::BF(const String& son)const
	{
		if (son.size == 0)return 0;
		size_t i=0,j;
		while (Data[i])
		{
			size_t tmpi = i;//
			j = 0;
			while (Data[tmpi] == son.Data[j])
			{
				if (Data[tmpi] == '\0' || son.Data[j] == '\0')break;
				tmpi++;
				j++;
			}
				
			if (j == son.size)return i+1;//返回匹配位置
			i++;
		}
		return 0;
	}

	size_t String::KMP(const String& son)const
	{
		size_t* nextval = son.Getnextval();
		size_t i = 0, j = 0;
		while (i < size)
		{
			if (Data[i] == son.Data[j])
			{
				i++;
				j++;
			}
			else if (j == 0)
			{
				i++;
			}
			else j = nextval[j];
			if (j == son.size)
			{
				delete[] nextval;
				return i - j + 1;
			}
		}
		delete[] nextval;
		return 0;
	}
	
	void String::AllocateMoreMemory()
	{
		capacity = capacity + capacity / 2 + 1;
		char* NewData = new char[capacity];

		for (size_t i = 0; i <= size; i++)
			NewData[i] = Data[i];
		delete []Data;
		Data = NewData;
	}
	void String::AllocateLessMemory()
	{
		capacity = capacity/2;
		char* NewData = new char[capacity];
		for (size_t i = 0; i <= size; i++)
			NewData[i] = Data[i];
		delete []Data;
		Data = NewData;
	}
}


namespace DSL
{
	size_t strlen(const char* str)
	{
		if (str == nullptr)return 0;
		size_t ret = 0;
		while (str[ret])ret++;

		return ret;
	}
	void strcopy(char* dst, const char* src)
	{
		while (*src)
			*dst++ = *src++;
	}
	void strcopy(char* dst, const std::string& src)
	{
		for (auto it = src.begin(); it != src.end(); it++)
			*dst++ = *it;
	}
}

