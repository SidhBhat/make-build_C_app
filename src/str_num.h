#ifndef STR_NUM_H_INCLUDED
#define STR_NUM_H_INCLUDED

#ifndef TYPE_BASE
#define TYPE_BASE 1
enum base {
	DEC = 10U,DECIMAL = 10U,
	HEX = 16U,HEXADECIMAL = 16U,
	OCT = 8U,OCTAL = 8U,
	BIN = 2U,BINARY = 2U,
};
#endif // TYPE_BASE

typedef short unsigned int base_t;

/*--------------String to Integer----------------------*/

//btoi : convert a string represnting a number with arthmetic base 'base', to it's inegral value and return it.
long long btoi(char const *num, base_t base);
/* Base is a number between 2-36, any other value in base will return 0.
 * Leading blank spaces are ignored.
 * A optional leading '0x' or '0X' may be given after the sign (and leading spaces) for hex strings.
 * A character that is not a valid digit for the arithmetic base 'base' terminates the string.
 * If the string represnts a number larger/smaller than the return type, then the maxi/min value of the return type is returned.
 */

/*--------------Special Values----------------*/

/*dtoi : converts a string, to it's  integer value and returns it*/
long long dtoi(char* str);
//behavior with string handling is identical to btoi.

/*htoi : converts a hex string, to it's  integer value and returns it*/
long long htoi(char* str);
//behavior with string handling is identical to btoi.

/*octtoi : converts a octal string, to it's  integer value and returns it*/
long long octtoi(char* str);
//behavior with string handling is identical to btoi.

/*bintoi : converts a binary string, to it's  integer value and returns it*/
long long bintoi(char* str);
//behavior with string handling is identical to btoi.

/*--------------Integer to String----------------------*/

//iotb : convert x to characters in str[], with the arthmetic base 'base'.
char *itob(long long int x, char *str, base_t base);
/* base is a number between 2U-36, any other value in base will make str a zero string and exit*/

//iotbw : convert x to charaters in str[], with the arthmetic base 'base'. Right adjust to width
char *itobw(long long int x, char* str, base_t base, short unsigned int width);
/* base is a number between 2U-36, any other value in base will make str a zero string and exit*/

/*--------------Special Values----------------*/

//iotd : convert x to characters in str[];
char *itod(long long int x, char *str);

//iotd : convert x to characters in str[]. Right adjust to width
char *itodw(long long int x, char *str, short unsigned int width);

//iota : convert x to hex characters in str[];
char *itoh(long long int x, char *str);

//iota : convert x to hex characters in str[]. Right adjust to width
char *itohw(long long int x, char *str, short unsigned int width);

//iota : convert x to octal characters in str[];
char *itooct(long long int x, char *str);

//iota : convert x to octal characters in str[]. Right adjust to width
char *itooctw(long long int x, char *str, short unsigned int width);

//iota : convert x to binary characters in str[];
char *itobin(long long int x, char *str);

//iota : convert x to binary characters in str[]. Right adjust to width
char *itobinw(long long int x, char *str, short unsigned int width);

/*------------------------------------------------------*/


#endif /* "str_num.h" */
