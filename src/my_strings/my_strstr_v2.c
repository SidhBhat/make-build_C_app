#include<stddef.h>

// function returns a pointer to the rightmost location where the string 'pattern' occurs in string str
char *my_strstr_v2(const char *str, const char *pattern)
{
	int i, j, k;
	char *ptr = NULL;

	for(i = 0; str[i] != '\0'; i++) {
		for( j = i, k = 0; pattern[k] != '\0' && str[j] == pattern[k]; j++, k++)
			;
		if(k > 0 && pattern[k] == '\0')
			ptr = (char *) &str[i];
	}

	return ptr;
}
