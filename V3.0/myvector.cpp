#include"myvector.h"
namespace DSL
{
	void vector_pop_back_test()
	{
		vector<int>v = { 1,2,3,4 };
		v.pop_back();
		for (auto it = v.begin(); it != v.end(); ++it)
			std::cout << *it << std::endl;
	}
	void vector_insert_test()
	{
		vector<std::string>v;
		v.insert(v.begin(), "LIWEI");
		v.insert(v.begin(), "HFLY");
		v.insert(v.begin(), "TIAN GUI");
		v.insert(v.begin(), "THE SHY");
		v.insert(v.begin(), "YASUO");
		for (auto it = v.begin(); it != v.end(); ++it)
			std::cout << *it << std::endl;
	}
	void vector_erase_test()
	{
		vector<std::string>v;
		v.insert(v.begin(), "LIWEI");
		v.insert(v.begin(), "HFLY");
		v.insert(v.begin(), "TIAN GUI");
		v.insert(v.begin(), "THE SHY");
		v.insert(v.begin(), "YASUO");
		v.erase(v.begin() + 1, v.end() - 1);
		for (auto it = v.begin(); it != v.end(); ++it)
			std::cout << *it << std::endl;
		//"LIWEI"
		//"YASUO"
	}
}