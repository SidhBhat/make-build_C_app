#include<stdio.h>

/* GetLine: read a line into s, return length */
unsigned int Getline(char *line ,unsigned int lim)
{
	int ch , i;

	for(i = 0 ; (ch = getchar()) != EOF && ch != '\n' ; i++)
		if(i < lim - 1)
			line[i] = ch;

	if(ch == '\n') {
		if(i < lim - 1)
			line[i++] = ch;
		else
			i++;
	}
	else if(ch == EOF) {
		putchar('\n');
		clearerr(stdin);
	}

	if(i <= lim - 1)
		line[i] = '\0';
	else
		line[lim - 1] = '\0';

	return i;
}
