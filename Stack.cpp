//#include"Stack.h"
//void StackTest()
//{
//	Stack<double>S;
//	//入栈测试
//	//{1.0,20,3.14159,2.718,77.777}
//	S.push(1.0f);
//	S.push(20);
//	S.push(3.14159);
//	S.push(2.718);
//	S.push(77.777);
//
//	//求深度测试
//	printf("Stack Depth is: %zu .\n", S.GetDepth());
//	//出栈测试
//	while (!S.empty())
//	{
//		std::cout << S.top() << std::endl;
//		S.pop();
//	}
//
//}
//
//void StackCopyConstructorTest()
//{
//	Stack<double>S;
//	
//	S.push(1.0f);
//	S.push(20);
//	S.push(3.14159);
//	S.push(2.718);
//	S.push(77.777);
//
//	Stack<double>newS = S;
//	while (newS.empty() == false)
//	{
//		std::cout << newS.top() << std::endl;
//		newS.pop();
//	}
//	//77.777 2.718 3.14159 20.0 1.0f
//}
//
//void LStackCopyConstructorTest()
//{
//	LStack<double>S;
//
//	S.push(1.0f);
//	S.push(20);
//	S.push(3.14159);
//	S.push(2.718);
//	S.push(77.777);
//
//	LStack<double>newS = S;
//	while (newS.empty() == false)
//	{
//		
//	}
//	//77.777 2.718 3.14159 20.0 1.0f
//}
