#include<stddef.h>
#include<endian.h>

#if __BYTE_ORDER == __LITTLE_ENDIAN

// Set the binary value stored in adress 'ptr' upto the size (in bytes), in string str .assume little endian
void getBits(size_t const size, void const *const ptr, char *str)
{
	unsigned char const *b = ptr;
	unsigned char byte;
	int i, j, k;

	k = 0;
	for (i = size-1; i >= 0; i--) {
		for (j = 7; j >= 0; j--) {
			byte = (b[i] >> j) & 1;
			str[k++] = '0' + byte;
		}
	}
	str[k] = '\0';
}

#elif __BYTE_ORDER == __BIG_ENDIAN

// Set the binary value stored in adress 'ptr' upto the size (in bytes), in string str .assume big endian
void getBits(size_t const size, void const *const ptr, char *str)
{
	unsigned char const *b = ptr;
	unsigned char byte;
	int i, j, k;

	k = 0;
	for (i = 0; i < size; i++) {
		for (j = 7; j >= 0; j--) {
			byte = (b[i] >> j) & 1;
			str[k++] = '0' + byte;
		}
	}
	str[k] = '\0';
}

#endif
