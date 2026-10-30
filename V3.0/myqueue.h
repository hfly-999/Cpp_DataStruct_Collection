#include"mylist.h"
#include"myvector.h"
namespace DSL
{
	template<typename Type, typename Container = list<Type>>
	class queue
	{
		Container c;
	public:
		void push(const Type& value) { c.push_back(value); }
		void pop() { c.pop_front(); }
		bool empty()const { return c.empty(); }
		const Type& back()const { assert(!empty()); return *(--c.end()); }
		const Type& front()const { assert(!empty()); return *(c.begin()); }
		size_t size() { return c.size(); }

	};



};
