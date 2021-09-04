//rightrotbits rotates the bits tn x to the right by n. (this means moving every bit on the left to the right by n, and filling the blanks on the right by bit that have fallen of the left border)
int rightrotbits(int x, short unsigned int n)
{
	return (unsigned)x >> n | (x & ~(~0U << n)) << (sizeof(x) * 8 - n);
}
