#include<stdio.h>
#include<float.h>
#include<math.h>

#define MAX_LINE_LENTH 1000

static char ld_str[MAX_LINE_LENTH + 2]; // required by str_add_exp() & strget.

/* replace char 'e' with "\e" in string */
static char *str_add_exp(char const *_ld_str)
{
	unsigned short int i, j;

	for(i = j = 0; _ld_str[i] != '\0' && j < MAX_LINE_LENTH - 1; i++) {
		if(_ld_str[i] == 'e' || _ld_str[i] == 'E')
			ld_str[j++] = '\\';
		ld_str[j++] = _ld_str[i];
	}
	ld_str[j++] = '\n';
	ld_str[j] = '\0';

	return ld_str;
}

/* copy: Copy from ld into ld_str: assume to is big enough */
static void strget(const char *_ld_str)
{
	int i;

	i = 0;
	while ((ld_str[i] = (i < MAX_LINE_LENTH - 1) ? _ld_str[i] : '\0') != '\0')
		++i;
	ld_str[i++] = '\n';
	ld_str[i] = '\0';
}

// btof : convert a string representing a number in arithmetic base 'base', to it's value.
long double btof(char const *_ld_str, unsigned short int base)
{
	long double ld_tmp;
	double power;
	short sign, tmp = 0;
	short exp = -1, k = 0;
	unsigned short i = 0, digit = 0;
	short const lim = (int)(LDBL_MANT_DIG * log(2) / log(base)) + 1;

	//check base
	if(base < 2 || base > 36)
		return 0.0L;
	if(base < 15)
		str_add_exp(_ld_str);
	else
		strget(_ld_str);

	while(ld_str[i] == ' ') // skip spaces
		i++;
	// check for sign
	if((ld_str[i] == '-') ? (sign = -1, 1) : (sign = 1, 0) || ld_str[i] == '+')
		i++;
	// if hex skip leading '0x' or '0X'
	if(base == 16 && ld_str[i] == '0' && (ld_str[i + 1] == 'x' || ld_str[i + 1] == 'X'))
		i += 2;

	//main loop
	for(ld_tmp = power = 0.0L; ld_str[i] != '\0'; i++) {
		if(k > 0 && k < lim)
			power *= base;
		if(ld_str[i] >= '0' && ld_str[i] < '0' + ((base < 10) ? base : 10))
			digit = ld_str[i] - '0', (k != -1) ? ++k : 0;
		else if(ld_str[i] >= 'A' && ld_str[i] < '0' + base +'A' - '9' - 1)
			digit = 10 + ld_str[i] - 'A', (k != -1) ? ++k : 0;
		else if(ld_str[i] >= 'a' && ld_str[i] < '0' + base +'a' - '9' - 1)
			digit = 10 + ld_str[i] - 'a', (k != -1) ? ++k : 0;
		else if(ld_str[i] == '.' && power == 0.0)
			power = (k > lim) ? (tmp = k - lim, k = -1, 1.0l) : 1.0l;
		else if(ld_str[i] == '\\' && (ld_str[i + 1] == 'e' || ld_str[i + 1] == 'E') && exp == -1) {
			power = (power == 0.0l) ? 1.0l : power / ((k >= lim || k < 0) ? 1.0L : (long double)base);
			ld_tmp = sign * ld_tmp / (long double)power ;
			power = 0.0l;
			++i;
			while(ld_str[++i] == ' ')
				;
			if((ld_str[i] == '-') ? (sign = -1, 1) : (sign = 1, 0) || ld_str[i] == '+') // check for sign
				;
			else
				--i;
			exp = 0;
			continue;
		}
		else
			break;
		if(exp == -1) {
			if(k > 0 && k <= lim)
				ld_tmp = (power != 1.0) ? ld_tmp * base + digit : ld_tmp;
		}
		else
			exp = exp * base + digit;
	}
	//finalise
	if(exp == -1) {
		power = (power == 0.0l) ? 1.0l : power / ((k >= lim || k < 0) ? 1.0L : (long double)base);
		ld_tmp = sign * ld_tmp / (long double)power;
	}
	else {
		exp = sign * exp + tmp;
// 		ld_tmp =  (exp < 0) ? (ld_tmp / powl(base, -exp)) : (ld_tmp * powl(base, exp));
		ld_tmp = ld_tmp * powl(base, exp);
	}

	return ld_tmp;
}
/* Base is between 2-36.
 * Leading spaces before mantissa and exponent are ignored.
 * Negative sign '-' or an optional '+' may be given before mantissa and exponent.
 * Any non-conforming characters terminate the string.
 * 'e' or 'E' represents the digit with value '14' and thus escape sequence "\e" or "\E" represents exponentiation.
 * 'e' or 'E' can still represent exponentiation for base lesser then 15.
 * the string must be lesser then 1000 characters.
 */
/* Dependencies :
 * function str_add_exp();
 * function strget()
 * char Array ld_str[];
 */
