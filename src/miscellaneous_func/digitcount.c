// digitcount : Counts the number of digits in 'num' if it were written in the Hindu-Araibic nummeral system, with arithmetic base 'base'.
unsigned short digitcount(long long num, unsigned short base)
{
	unsigned short n_digits;

	//check validity of base
	if(base < 2 || base > 36)
		return 0;

	for(n_digits = 1; (num /= base) != 0; n_digits++)
		;

	return n_digits;
}
