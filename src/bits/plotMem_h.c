#include<stdio.h>
#include<unistd.h>
#include<sys/ioctl.h>

extern struct winsize w;
/*prints the binary value stored in adress 'ptr' upto the size (in bytes).*/
void printBits(const size_t size, const void*const ptr);

// plotMem_h: plot the data in *ptr upto 'size' in horizontal rows
void plotMem_h(const size_t size, void const *const ptr)
{
	const unsigned char *byte = ptr;
	int i, j;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	if((w.ws_col -= 16) < size * 16) {
		printf("\x1b[1;31mprintmem Error\x1b[0m : The console width is too small to plot.\n");
		printf("Minimum required width : %lu\n", (size + 1) * 16);
		return;
	}

	printf("---------------|");
	for(i = 0; i < size;  i++){
		for(j = 0; j < w.ws_col / size / 2 * 2 - 1; j++)
			putchar('-');
		putchar('|');
	}
	printf("\nMemory Address |");
	for(i = 0; i < size; i++) {
		for(j = 0; j < (w.ws_col / size - 14) / 2; j++)
			putchar(' ');
		printf("%p", &byte[i]);
		for(j = 0; j < (w.ws_col / size - 14) / 2 - 1; j++)
			putchar(' ');
		putchar('|');
	}
	printf("\n---------------|");
	for(i = 0; i < size;  i++){
		for(j = 0; j < w.ws_col / size / 2 * 2 - 1; j++)
			putchar('-');
		putchar('|');
	}
	printf("\nData (bin)     |");
	for(i = 0; i < size; i++) {
		for(j = 0; j < (w.ws_col / size - 8) / 2; j++)
			putchar(' ');
		printBits(sizeof(byte[i]), &byte[i]);
		for(j = 0; j < (w.ws_col / size - 8) / 2 - 1; j++)
			putchar(' ');
		putchar('|');
	}
	printf("\nData (hex)     |");
	for(i = 0; i < size; i++) {
		for(j = 0; j < (w.ws_col / size - 8) / 2; j++)
			putchar(' ');
		printf("%5x   ",byte[i]);
		for(j = 0; j < (w.ws_col / size - 8) / 2 - 1; j++)
			putchar(' ');
		putchar('|');
	}
	printf("\n---------------|");
	for(i = 0; i < size;  i++){
		for(j = 0; j < w.ws_col / size / 2 * 2 - 1; j++)
			putchar('-');
		putchar('|');
	}
	putchar('\n');
}
