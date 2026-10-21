//#include"Stack.h"
//using namespace DSL;
///*----------------------------------------------------------------*/
////顺序栈
//template<typename type>
//Stack<type>::Stack():L()
//{
//	//std::cout << "声明了栈" << std::endl;
//};
////拷贝构造函数
//template<typename type>
//Stack<type>::Stack(const Stack& obj):L(obj.L)
//{
//
//}
//template<typename type>
//Stack<type>::~Stack()
//{
//	//std::cout << "销毁了栈" << std::endl;
//}
//template<typename type>
//void Stack<type>::pop()
//{
//	L.DeleteTailElement();//返回栈顶元素
//}
//template<typename type>
//type Stack<type>::top() const
//{
//	return L.Find(L.Getsize()-1);
//	
//}
//template<typename type>
//bool Stack<type>::empty()const
//{
//	if (L.Getsize() == 0)return true;//如果栈深度是0
//	return false;
//}
//
//template<typename type>
//void Stack<type>::push(type element)
//{
//	L.push_back(element);//没有满则把元素加入栈中,并且让栈顶指针自增
//}
//template<typename type>
//size_t Stack<type>::GetDepth()const
//{
//	return L.Getsize();//返回栈深
//}
//
//template<typename type>
//type Stack<type>::GetTop() const
//{
//	return L[L.Getsize() - 1];
//}
///*----------------------------------------------------------------*/
////链式栈
//template<typename type>
//LStack<type>::LStack():L()//调用了链表的无参构造函数
//{
//
//}
//template<typename type>
//LStack<type>::LStack(const LStack& obj):L(obj.L)
//{
//
//}
//template<typename type>
//LStack<type>::~LStack()
//{
//
//}
//template<typename type>
//void LStack<type>::pop()
//{
//
//	L.HeadDelete();
//}
//template<typename type>
//const type LStack<type>::top()const
//{
//	return L.GetFirstNodeValue();
//}
//template<typename type>
//void LStack<type>::push(type element)
//{
//	L.HeadInsert(element);
//}
//
//template<typename type>
//size_t LStack<type>::GetDepth()const
//{
//	return L.GetLength();
//}
//template<typename type>
//bool LStack<type>::empty()const
//{
//	return L.empty();
//}
//template<typename type>
//type LStack<type>::GetTop()const
//{
//	return L.GetFirstNodeValue();
//}