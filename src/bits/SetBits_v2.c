#include<stddef.h>
#include<endian.h>

#if __BYTE_ORDER == __LITTLE_ENDIAN

// Write the binary string in bits, to address '*var' upto size(in bytes)
void SetBits_v2(size_t const size, void *const var, char const *const bits)
{
	unsigned char tmp, *val = var;
	int i, j, k;

	for(i = 0; bits[i] == '1' || bits[i] == '0'; i++)
		;
	if(i < size * 8)
		return;
	*val = 0;

	for(i = j = 0; i < size * 8; i++) {
		*val <<= 1;
		*val |= (bits[j++] == '1') ? 1 : 0;
		if(j % 8 == 0 && (bits[j] == '1' || bits[j] == '0')) {
			for(k = 1; k <= j / 8; k++) {
				tmp = *val;
				*val = *(val + k);
				*(val + k) = tmp;
			}
			*val = 0;
		}
	}
}
/* The string is read left-right.
 * For a string larger then size, (size * 8 bits) only the first 'size * 8' bits are taken into account.
 * A quirk of this version is that strings smaller than 'size * 8' are not accepted.
 * Any other character other than '1' or '0' terminates the string.
 */

#elif __BYTE_ORDER == __BIG_ENDIAN

// Write the binary string in bits, to address '*var' upto size(in bytes).
void SetBits_v2(size_t const size, void *const var, char const *const bits)
{
	unsigned char *val = var;
	int i, j;


	for(i = 0; bits[i] == '1' || bits[i] == '0'; i++)
		;
	if(i < size * 8)
		return;
	*val = 0;

	for(i = j = 0; i < size * 8; i++) {
		*val <<= 1;
		*val |= (bits[j++] == '1') ? 1 : 0;
		if(j % 8 == 0 && (bits[j] == '1' || bits[j] == '0'))
			*(++val) = 0;
	}
}
/* The string is read left-right.
 * For a string larger then size, (size * 8 bits) only the first 'size * 8' bits are taken into account.
 * A quirk of this version is that strings smaller than 'size * 8' are not accepted.
 * Any other character other than '1' or '0' terminates the string.
 */

#endif
