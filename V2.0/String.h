#pragma once
#include"Define.h"

namespace DSL
{
	unsigned int Strlen		
		(const char* str);
	unsigned int BF			
		(const char* pattern, const char* son);
	unsigned int KMP
		(const char* pattern, const char* son);
};

