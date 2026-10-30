#include"myvector.h"
namespace DSL
{
	template<typename Type,typename Container=vector<Type>>
	class stack
	{
		Container c;
	public:
		void push(Type value) { c.push_back(value); }
		void pop() { c.pop_back(); }
		Type& top()
		{
			assert(!empty());
			return *(c.end() - 1);
		}
		const Type& top()const
		{
			assert(!empty());
			return *(c.end() - 1);
		}
		bool empty()const
		{
			return !c.size();
		}
		size_t size() { return c.size(); }
	};
};

