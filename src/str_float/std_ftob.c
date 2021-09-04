// ftobg : automatically select wether to call ftob or ftobe.
char *ftobg(long double ld, char *str, unsigned short int n_digits, unsigned short int base);

#define BASE 10U

// ftod : convert a long double value to a decimal character representation in string str.
char *ftod(long double ld, char *str, unsigned short int n_digits)
{
	return ftobg(ld, str, n_digits, BASE);
}
//behaviour identical to ftobg.

#undef BASE
#define BASE 16U

// ftoh : convert a long double value to a hexadecimal character representation in string str.
char *ftoh(long double ld, char *str, unsigned short int n_digits)
{
	return ftobg(ld, str, n_digits, BASE);
}
//behaviour identical to ftobg.

#undef BASE
#define BASE 8U

// ftooct : convert a long double value to a octal character representation in string str.
char *ftooct(long double ld, char *str, unsigned short int n_digits)
{
	return ftobg(ld, str, n_digits, BASE);
}
//behaviour identical to ftobg.

#undef BASE
#define BASE 2U

// ftobin : convert a long double value to a binary character representation in string str.
char *ftobin(long double ld, char *str, unsigned short int n_digits)
{
	return ftobg(ld, str, n_digits, BASE);
}
//behaviour identical to ftobg.

#undef BASE
