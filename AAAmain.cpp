#include"mylist.h"
#include"myvector.h"
#include<vector>
#include<list>

using namespace DSL;

int main()
{
	vector<int>v = { 1,2,3,4,5 };
	const vector<int>& rv = v;

	for (auto it = rv.begin(); it != rv.end(); ++it)
	{
		std::cout << *it<<"\n";
	}
}