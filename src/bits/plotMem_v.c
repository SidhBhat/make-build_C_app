#include<stdio.h>
#include<unistd.h>
#include<sys/ioctl.h>

#define PLOTMEM_V_MIN_WITDH 45

extern struct winsize w;
/*prints the binary value stored in adress 'ptr' upto the size (in bytes).*/
void printBits(const size_t size, const void*const ptr);

// plotMem_v: plot the data in *ptr upto 'size' in vertical columns
void plotMem_v(const size_t size, const void*const ptr)
{
	const unsigned char *byte = ptr;
	int i;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	if(w.ws_col < PLOTMEM_V_MIN_WITDH) {
		printf("\x1b[1;31mprintmem Error\x1b[0m : The console width is too small to plot.\n");
		printf("Minimum required width : %d\n", PLOTMEM_V_MIN_WITDH);
		return;
	}

	printf("|-----------------|------------|------------|\n");
	printf("| Memmory Address | Data (bin) | Data (hex) |\n");
	for(i = 0; i < size; i++) {
		printf("|-----------------|------------|------------|\n");
		printf("| %p  |  ", &byte[i]);
		printBits(sizeof(byte[i]), &byte[i]);
		printf("  |%7x     |\n", byte[i]);
	}
	printf("|-----------------|------------|------------|\n");

	putchar('\n');
}
