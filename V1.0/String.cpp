#include"String.h"
/*
unsigned int KMP(const char* dst, const char* src)
{
	int i = 0, j = 0;//母串指针,子串指针
	while (src[j])j++;

	unsigned int* next = (unsigned int*)malloc(j * sizeof(unsigned int));
	next[0] = 0;
	j = 1;
	int tmp = 0;//最长公共前后缀
	while (src[j])
	{
		if (src[j] == next[tmp])
		{
			tmp++;
			next[j] = tmp;
			j++;
		}
		else
		{
			if (tmp == 0)
			{
				next[j] = 0;
				j++;
			}
			else//回溯到上一个地方
			{
				tmp = next[tmp - 1];
			}

		}
	}
	j = 0;
	while (dst[i])
	{
		if (dst[i] == src[j])
		{
			i++;
			j++;
		}
		else if (next[j] == 0)
		{
			i++;
		}
		else
		{
			j = next[j];
		}

		if (src[j] == '\0')return i - j + 1;// 0 1 2 3  //1 2 3

	}
	return 0;

}*/