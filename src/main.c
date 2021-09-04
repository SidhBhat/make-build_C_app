#include<stdio.h>
#include"my_strings.h"

#define MAXLINE 300

extern void PrintData(char *);

int main(void)
{
	char str[MAXLINE];

	printf("Type a number : ");
	Getline(str, sizeof(str));
	{
		int i;
		for(i = 0; str[i] != '\n';i++)
			;
		str[i] = '\0';
	}
	PrintData(str);
	return 0;
}
