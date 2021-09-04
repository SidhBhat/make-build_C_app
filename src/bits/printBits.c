#include<stdio.h>
#include<endian.h>

#if __BYTE_ORDER == __LITTLE_ENDIAN

/*prints the binary value stored in adress 'ptr' upto the size (in bytes) .assume little endian*/
void printBits(size_t const size, void const *const ptr)
{
	unsigned char const *b = ptr;
	unsigned char byte;
	int i, j;

	for (i = size-1; i >= 0; i--) {
		for (j = 7; j >= 0; j--) {
			byte = (b[i] >> j) & 1;
			printf("%u", byte);
		}
	}
}

#elif __BYTE_ORDER == __BIG_ENDIAN

/*prints the binary value stored in adress 'ptr' upto the size (in bytes) .assume big endian*/
void printBits(size_t const size, void const *const ptr)
{
	unsigned char const *b = ptr;
	unsigned char byte;
	int i, j;

	for (i = 0; i < size; i++) {
		for (j = 7; j >= 0; j--) {
			byte = (b[i] >> j) & 1;
			printf("%u", byte);
		}
	}
}

#endif
