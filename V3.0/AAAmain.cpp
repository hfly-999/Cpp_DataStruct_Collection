
#include"String.h"


using namespace DSL;
void warnness()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
}
int main()
{
	String str1 = "123456789JKLOVE";
	String str2 = "789";
	std::cout << str1.KMP(str2);

}