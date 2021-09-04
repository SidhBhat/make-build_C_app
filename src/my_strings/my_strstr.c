#include<stddef.h>

// function returns a pointer to the first location where the string 'pattern' occurs in string str
char *my_strstr(const char *str, const char *pattern)
{
	int i, j, k;

	for(i = 0; str[i] != '\0'; i++) {
		for( j = i, k = 0; pattern[k] != '\0' && str[j] == pattern[k]; j++, k++)
			;
		if(k > 0 && pattern[k] == '\0')
			return (char *) &str[i];
	}

	return NULL;
}
