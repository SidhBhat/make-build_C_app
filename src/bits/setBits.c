/* Reurns the intger value of the input binary string. */
int setBits(char const *const bits)
{
	int i, x;

	x = 0;
	for(i = 0 ; i < sizeof(x) * 8 && (bits[i] == '1' || bits[i] == '0'); i++) {
		x <<= 1;
		x |= (bits[i] == '1') ? 1 : 0;
	}

	return x;
}
/* The string is read left-right.
 * The leftmost bits are filled first, therfore for a sring longer then 32 bits(sizeof int) only the first 32 bits(sizeof int) from the leftmost side is taken.
 * For a string containing char that are not '1' or '0', the return value is the value of the binary string before the first non '1' or '0' char.
 * If first char is a non '1'or '0' char then the return value is 0.
 */
