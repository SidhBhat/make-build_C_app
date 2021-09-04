#include<math.h>

// ftob : convert a long double value to a character representation in string str, with arithmetic base 'base'.
char *ftob(long double ld, char *str, unsigned short int n_digits, unsigned short int base);
// ftobe : convert a long double value to a character representation in string str - in scientific notation - with arithmetic base 'base'.
char *ftobe(long double ld, char *str, unsigned short int n_digits, unsigned short int base);

// ftobg : automatically select wether to call ftob or ftobe.
char *ftobg(long double ld, char *str, unsigned short int n_digits, unsigned short int base)
{
	if(ld > pow(base, -n_digits) && ld < pow(base, n_digits))
		return ftob(ld, str, n_digits, base);
	else
		return ftobe(ld, str, n_digits, base);
}
