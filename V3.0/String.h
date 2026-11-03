#pragma once
#include"Define.h"
#include"Include.h"
#include"myvector.h"

namespace DSL
{

	class String
	{
		
		DSL::vector<char>string;
	public:
		//String();
		String(const char* str) { while (*str)string.push_back(*str++);}		//常量字符串构造
		String(const std::string& str = "") { for (auto it = str.begin(); it != str.end(); ++it)string.push_back(*it);}	//std::string构造
		String(const std::initializer_list<char>& ls):string(ls) {}				//inilializer_list构造
		String(const String& obj) :string(obj.string) {}						//拷贝构造函数
		

		~String()=default;					//析构


		//iterator
		const char* begin()const { return string.begin(); }
		char* begin() { return string.begin(); }
		const char* end()const { return string.end(); }
		char* end() { return string.end(); }
		//operator over load
		char& operator[](size_t index) { assert(index < string.size()); return string[index]; }
		const char& operator[](size_t index)const { assert(index < string.size()); return string[index]; }
		String& operator=(const String& rhs) { string = rhs.string; return *this; }


		size_t size()const { return string.size(); }
		size_t capacity()const { return string.capacity(); }
		bool empty()const { return string.empty(); }

		vector<size_t> Getnext()const;		//获取该串的next数组
		vector<size_t> Getnextval()const;	//获取该串的nextval数组

		size_t BF(const String& son)const;	//暴力找到子串在母串当中的位置
		size_t KMP(const String& son)const;	//KMP算法找子串首位置
	};


	

};





































