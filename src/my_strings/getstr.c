#include<stdio.h>

/* getstr: read a string into s, return length */
unsigned int getstr(char *str, unsigned int lim)
{
	int ch, i;

	for(i = 0; (ch = getchar()) != EOF ; i++)
		if(i < lim - 1)
			str[i] = ch;

	if(i <= lim - 1)
		str[i] = '\0';
	else
		str[lim - 1] = '\0';

	clearerr(stdin);
	putchar('\n');

	return i;
}
