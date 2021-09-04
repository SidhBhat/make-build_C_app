#include<stddef.h>
#include<endian.h>

#if __BYTE_ORDER == __LITTLE_ENDIAN

// Write the binary string in bits, to address '*var' upto size(in bytes).
void SetBits(size_t const size, void *const var, char const *const bits)
{
	unsigned char one, *val = var;
	int i, k;

	one = 1;
	for(i = 0; i < size; i++)
		val[i] = 0;
	for(k = 0; bits[k] == '1' || bits[k] == '0'; k++)
		;
	k = (k > size * 8) ? (size * 8) : k;

	for(i = k - 1; i >= 0; i--) {
		*val |= (bits[i] == '1') ? one : 0;
		one <<= 1;
		if((k - i) % 8 == 0) {
			*(++val) = 0;
			one = 1;
		}
	}
}
/* The string is read left-right.
 * For a string larger then size, (size * 8 bits) only the first 'size * 8' bits are taken into account.
 * For a string smaller then size (size * 8 bits), bits are filled from the right, with the leftmost bit as the most significant.
 * Any other character other than '1' or '0' terminates the string.
 * A null/zero string is interpreted as 0.
 */

#elif __BYTE_ORDER == __BIG_ENDIAN

// Write the binary string in bits, to address '*var' upto size(in bytes).
void SetBits(size_t const size, void *const var, char const *const bits)
{
	unsigned char one, *val = var;
	int i, k;

	one = 1;
	for(i = *(val) = 0; i < size - 1; i++)
		*(++val) = 0;
	for(k = 0; bits[k] == '1' || bits[k] == '0'; k++)
		;
	k = (k > size * 8) ? (size * 8) : k;

	for(i = k - 1; i >= 0; i--) {
		*val |= (bits[i] == '1') ? one : 0;
		one <<= 1;
		if((k - i) % 8 == 0) {
			--val;
			one = 1;
		}
	}
}
/* The string is read left-right.
 * For a string larger then size, (size * 8 bits) only the first 'size * 8' bits are taken into account.
 * For a string smaller then size (size * 8 bits), bits are filled from the right, with the leftmost bit as the most significant.
 * Any other character other than '1' or '0' terminates the string.
 * A null/zero string is interpreted as 0.
 */

#endif
