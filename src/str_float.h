#ifndef STR_FLOAT_H
#define STR_FLOAT_H 1

#ifndef TYPE_BASE
#define TYPE_BASE 1
enum base {
	DEC = 10U,DECIMAL = 10U,
	HEX = 16U,HEXADECIMAL = 16U,
	OCT = 8U,OCTAL = 8U,
	BIN = 2U,BINARY = 2U,
};
#endif // TYPE_BASE

/*----------------Float to String------------------*/

// ftob : convert a long double value to a character representation in string str, with arithmetic base 'base'.
char *ftob(long double ld, char *str, unsigned short int n_digits, unsigned short int base);
/* Base is between 2-36.
 * Argument 'n_digits' must be lesser then size of str.
 * the string is only precisise for LDBL_MANT_DIG * log(2) * log(base) digits, in base (about 19 digits in decimal).
 */

// ftob : convert a long double value to a character representation in string str - in scientific notation - with arithmetic base 'base'.
char *ftobe(long double ld, char *str, unsigned short int n_digits, unsigned short int base);
/* Base is between 2-36.
 * Argument 'n_digits' must be lesser then size of str.
 * the string is only precisise for LDBL_MANT_DIG * log(2) * log(base) digits, in base (about 19 digits in decimal).
 */

// ftobg : automatically select wether to call ftob or ftobe.
char *ftobg(long double ld, char *str, unsigned short int n_digits, unsigned short int base);

/*----------------Spesific values------------------*/

// ftod : convert a long double value to a decimal character representation in string str.
char *ftod(long double ld, char *str, unsigned short int n_digits);
//behaviour identical to ftobg.

// ftoh : convert a long double value to a hexadecimal character representation in string str.
char *ftoh(long double ld, char *str, unsigned short int n_digits);
//behaviour identical to ftobg.

// ftooct : convert a long double value to a octal character representation in string str.
char *ftooct(long double ld, char *str, unsigned short int n_digits);
//behaviour identical to ftobg.

// ftobin : convert a long double value to a binary character representation in string str.
char *ftobin(long double ld, char *str, unsigned short int n_digits);
//behaviour identical to ftobg.

/*----------------String to Float------------------*/

// btof : convert a string representing a number in arithmetic base 'base', to it's value.
long double btof(char const *ld, unsigned short int base);
/* Base is between 2-36.
 * Leading spaces before mantissa and exponent are ignored.
 * Negetive sign '-' or an optional '+' may be given before mantissa and exponent.
 * Any non-conforming characters terminate the string.
 * 'e' or 'E' represents the digit with value '14' and thus escape sequnce "\e" or "\E" represents exponetation.
 * 'e' or'E' can still represent exponentation for base lesser then 15.
 * the string must be lesser then 1000 characters.
 */

/*----------------Spesific values------------------*/

// dtof : convert a string representing a number in decimal , to it's value.
long double dtof(char const *ld);
// string handling is identical to btof.

// atoh : convert a string representing a number in hexadecimal , to it's value.
long double htof(char const *ld);
// string handling is identical to btof.

// octtof : convert a string representing a number in octal , to it's value.
long double octtof(char const *ld);
// string handling is identical to btof.

// bintof : convert a string representing a number in binary , to it's value.
long double bintof(char const *ld);
// string handling is identical to btof.

#endif /* "str_float.h" */
