#include<limits.h>

//btoi : convert a string representing a number with arithmetic base 'base', to it's integral value and return it.
long long int btoi(char const *num_str, unsigned short int base)
{
	//declarations
	unsigned long long x;
	short unsigned i = 0;
	short sign = 1;

	//check validity of base
	if(base < 2 || base > 36)
		return 0;

	while(num_str[i] == ' ') // skip leading blanks
		i++;
	// check for sign
	if((num_str[i] == '-') ? (sign = -1,1) : 0 || num_str[i] == '+')
		i++;
	// if hex skip leading '0x' or '0X'
	if(base == 16 && num_str[i] == '0' && (num_str[i + 1] == 'x' || num_str[i + 1] == 'X'))
		i += 2;

	//main loop
	for(x = 0; num_str[i] != '\0'; i++) {
		if(x >= LLONG_MAX)
			return sign * (signed long long)LLONG_MAX;
		if(num_str[i] >= '0' && num_str[i] < '0' + ((base < 10) ? base : 10))
			x = x * base + num_str[i] - '0';
		else if(num_str[i] >= 'A' && num_str[i] < '0' + base +'A' - '9' - 1)
			x = x * base + 10 + num_str[i] - 'A';
		else if(num_str[i] >= 'a' && num_str[i] < '0' + base +'a' - '9' - 1)
			x = x * base + 10 + num_str[i] - 'a';
		else
			break;

	}

	return sign * (signed long long)x;
}
/* Base is a number between 2-36, any other value in base will return 0.
 * Leading blank spaces are ignored.
 * A optional leading '0x' or '0X' may be given after the sign (and leading spaces) for hex strings.
 * A character that is not a valid digit for the arithmetic base 'base' terminates the string.
 * If the string represents a number larger/smaller than the return type, then the maxi/min value of the return type is returned.
 */
