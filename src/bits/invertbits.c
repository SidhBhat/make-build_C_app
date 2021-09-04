//if p is position from zero, invertbits inverts (takes the compliment of) n bits from p and leaves the rest unchanged
int invertbits(int x, short unsigned int p, short unsigned int n)
{
	// 	return (x & ~(~(~0 << n) << p)) | ~(x | ~(~(~0 << n) << p)); //my first version
	return x ^ (~(~0 << n) << p); //efficent version
}
