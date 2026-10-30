#include"mylist.h"
#include"myvector.h"
#include"Tree.h"
#include<vector>
#include<list>

using namespace DSL;
void warnness()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
}
int main()
{
	btree_insert_test();
}