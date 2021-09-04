// btof : convert a string representing a number in arithmetic base 'base', to it's value.
long double btof(char const *_ld_str, unsigned short int base);

#define BASE 10U

// dtof : convert a string representing a number in decimal , to it's value.
long double dtof(char const *ld)
{
	return btof(ld, BASE);
}
// string handling is identical to btof.

#undef BASE
#define BASE 16U

// htof : convert a string representing a number in hexadecimal, to it's value.
long double htof(char const *ld)
{
	return btof(ld, BASE);
}
// string handling is identical to btof.

#undef BASE
#define BASE 8U

// octtof : convert a string representing a number in octal, to it's value.
long double octtof(char const *ld)
{
	return btof(ld, BASE);
}
// string handling is identical to btof.

#undef BASE
#define BASE 2U

// bintof : convert a string representing a number in binary, to it's value.
long double bintof(char const *ld)
{
	return btof(ld, BASE);
}
// string handling is identical to btof.

#undef BASE
