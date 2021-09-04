/*if p is position from zero, changebits takes n bits from var y (starting zero), and places it at position p in x the remaing bits unchanged*/
int changebits(int x, short unsigned int p,  short unsigned int n, int y)
{
	x = x & (~((~(~0 << n)) << p));
	y = (y & (~(~0 << n))) << p;

	return x ^ y;
}
