#include"String.h"
namespace DSL
{

	size_t* String::Getnext()const
	{
		size_t* PM = new size_t[string.size()];//部分匹配值,记得被回收
		PM[0] = 0;
		size_t count = 0;//最长公共前后缀
		for (auto it = begin()+1; it != end(); )
		{
			if (*it == string[count])
			{
				PM[it - begin()] = count;
				++it;
				++count;
			}
			else if (count == 0)
			{
				PM[it - begin()] = count;
				++it;
			}
			else
			{
				count = PM[count - 1];//回溯
			}	
		}
		for (size_t i = 1; i < size(); ++i)
		{
			PM[i] = PM[i - 1];
		}
		return PM;
	}

	size_t* String::Getnextval()const
	{
		size_t* next = Getnext();
		for (size_t i = 1; i < size(); ++i)
			while (string[i] == string[next[i]] && next[i] != 0)next[i] = next[next[i]];
		return next;
	}

	size_t String::BF(const String& son)const
	{
		auto it_this = begin();
		auto it_son = son.begin();
		while (1)
		{
			auto it_this_tmp = it_this;
			auto it_son_tmp = it_son;
			while (*it_this_tmp == *it_son_tmp)
			{
				++it_this_tmp;
				++it_son_tmp;
				if (it_son_tmp == son.end())return it_this - begin() + 1;
			}
			++it_this;
			if (it_this == end())return 0;//没找到
		}
	}
	
	size_t String::KMP(const String& son)const
	{
		size_t *nextval=son.Getnextval();
		auto it_son = son.begin();
		for (auto it = begin(); it != end(); )
		{
			if (*it == *it_son)
			{
				++it;
				++it_son;
			}
			else if (it_son != son.begin())
			{
				it_son = son.begin() + nextval[it_son - son.begin()];
			}
			else ++it;
			if (it_son == son.end())return (it - begin()) - (it_son - son.begin()) + 1;
		}
		return 0;
		
	}
}






