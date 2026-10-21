#pragma once
#include"Define.h"
#include"Include.h"

//链表模块
namespace DSL
{
	template<typename type>
	class LinkList;
	
	//链表节点
	template<typename type>
	class LNode
	{
	public:
		//构造
		LNode(type value = type{}) :
			value(value),
			next(nullptr){};
		//拷贝构造
		LNode(const LNode& obj) :
			value(obj.value),
			next(nullptr){}
		~LNode()=default;

		friend class LinkList<type>;

	private:
		type value;
		LNode* next;
	};

};
namespace DSL
{
	//链表
	template<typename type>
	class LinkList
	{
	public:
		//constructor/copy constructor/desconstructor
		LinkList();							//无参构造
		LinkList(const LinkList& obj);		//拷贝构造
		virtual ~LinkList();				//无参析构
		//operator over load
		LinkList& operator=(const LinkList& that);//=运算符重载
		//add
		void HeadInsert(type element);		//头插
		void push_back(type element);		//尾插
		////delete
		//type HeadDelete();					//头删
		//type TailDelete();					//尾删
		
		////change
		////find
		//void Visit() const;				    //访问链表
		bool empty() const;					//链表是否为空
		//type GetFirstNodeValue()const;		//获取链表首节点元素值
		//size_t GetLength() const;			//获取链表长度

		

	private:
		static void LinkMemoryfree(LNode<type>* node);
		LNode<type>* Head;
		LNode<type>* Tail;
	};
	
}





#include"LinkList.inl"



void LinkListHeadInsertTest();

void LinkListpush_backTest();

void LinkListHeadDeleteTest();

void LinkListTailDeleteTest();

void LinkListCopyConstructorTest();//拷贝构造函数测试

void LinkListEqualTest();

void LinkListIsEqualTest();