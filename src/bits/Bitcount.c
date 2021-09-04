//counts the number of bits that have value 1 in var x.
int Bitcount(int x)
{
	int b;

	for(b = 0 ; x ; x &= x - 1)
		b++;

	return b;
}
