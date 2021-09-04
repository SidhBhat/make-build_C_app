#include<stddef.h>

// function to conpare s1 and s2, and return the position (as pointer to array) to the first location in s1 where any character from s2 occurs (order of chars in s2 does not matter)
char *my_strpbrk(const char *str1, const char *str2)
{
	int i, j, pos;

	pos = -1;
	for(i = 0 ; str2[i] != '\0' ; i++)
		for(j = 0 ; str1[j] != '\0' ; j++)
			if(str1[j] == str2[i] && j < (unsigned)pos)
				pos = j;
	if(pos >= 0)
		return (char *) &str1[pos];
	else
		return NULL;
}
