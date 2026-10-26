#pragma once

#include"Define.h"
#include"Include.h"
namespace DSL
{
	template<typename Object>
	class Unique_ptr
	{
		Object* ptr;//指向对象的指针
	public:
		Unique_ptr<Object>(Object* obj) :ptr(obj) {};
		Unique_ptr(const Unique_ptr<Object>& obj) = delete;//禁止拷贝构造
		virtual ~Unique_ptr()
		{
			delete ptr;//释放指针所拥有的资源
		}
		void Release()
		{
			delete ptr;//释放指针所拥有的资源
		}
		
	};
	
	
}


