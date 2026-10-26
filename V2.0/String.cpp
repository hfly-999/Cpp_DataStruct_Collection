#include"String.h"

unsigned int Strlen(const char* str)
{
	unsigned long long ret = 0;
	while (str[ret])ret++;
	return ret;
}

unsigned int BF(const char* pattern, const char* son)
{
	unsigned long long i = 0;
	while (pattern[i])
	{
		unsigned long long tag = i;//记录pattern对比的起始位置
		unsigned long long j = 0;
		while (pattern[tag]==son[j])
		{
			tag++;
			j++;
			if (son[j] == '\0')return i + 1;
		}
		i++;
			
	}
	return 0;//没找到

}

unsigned int KMP(const char* pattern, const char* son)
{
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int sonlen = Strlen(son);
	unsigned int* PM = (unsigned int*)malloc(sonlen * sizeof(int));
	unsigned int* next = (unsigned int*)malloc(sonlen * sizeof(int));
	if (PM == nullptr||next==nullptr)return 0;
	PM[0] = 0;
	j = 1;
	unsigned int count = 0;//最长公共前后缀
	while (son[j])
	{
		if (son[j] == son[count])
		{
			count++;
			PM[j++] = count;
		}
		else
		{
			if (count == 0)
			{
				PM[j++] = 0;
			}
			else
			{
				count = PM[count - 1];//回溯最长公共前后缀
			}
		}
	}
	next[0] = 0;
	for (unsigned int k = 0; k < sonlen - 1; k++)
		next[k+1] = PM[k];
	for (unsigned int k = 0; k < sonlen; k++)
		while (son[k] == son[next[k]]&&next[k]!=0)
			next[k] = next[next[k]];
	//next->nextval
	j = 0;
	while (pattern[i])
	{
		if (pattern[i] == son[j])
		{
			i++;
			j++;
		}
		else
		{
			if (j == 0)
				i++;
			else j = next[j];

		}
		if (son[j] == '\0')return i - j + 1;
	}
	return 0;
}