#pragma once
#include"Define.h"
#include"Include.h"

//size_t BF();

//size_t KMP();
namespace DSL
{
	class String
	{
		
		size_t size;//实际数据使用的大小,不包含'\0'
		size_t capacity;//已经申请的内存大小
		char* Data;
	public:
		//String();
		String(const char* str);			//常量字符串构造
		String(const std::string& str="");	//std::string构造
		String(const String& obj);			//拷贝构造函数
		virtual ~String();					//虚析构
		size_t* Getnext()const;				//获取该串的next数组
		size_t* Getnextval()const;			//获取该串的nextval数组
		size_t Getsize()const;				//获取字符串大小
		size_t GetCapacity()const;			//获取容器大小
		size_t BF(const String& son)const;	//暴力找到子串在母串当中的位置
		size_t KMP(const String& son)const;	//KMP算法找子串首位置
		void AllocateMoreMemory();			//扩容
		void AllocateLessMemory();			//减容
	};


	

};
namespace DSL
{
	/*-------------------------string.h---------------------------*/

	size_t strlen(const char* str);				//计算字符串长度
	void strcopy(char* dst, const char* src);	//复制字符串
	void strcopy(char* dst, const std::string& src);//复制字符串
	/*-------------------------string.h---------------------------*/
}

namespace DSL
{
	void BFTest1();
	void KMPTest1();
}




































