#include<stddef.h>
#include<string.h>
#include<math.h>

// ftobe : convert a long double value to a character representation in string str - in scientific notation - with arithmetic base 'base'.
char *ftobe(long double ld, char *str, unsigned short int n_digits, unsigned short int base)
{
	long double ftob_tmp;
	short unsigned index = 1;
	short int i = 0, j = 0, k;
	short const sign = (signbit(ld)) ? -1 : 1;

	//check base, number.
	if(base < 2 || base > 36)
		return NULL;
	else if(ld == INFINITY)
		return strcpy(str, "inf");
	else if(ld == -INFINITY)
		return strcpy(str, "-inf");
	else if(isnan(ld))
		return strcpy(str, "nan");
	//initialisations
	(sign == -1) ? str[i++] = '-' : 0;
	ftob_tmp = sign * ld;
	//generate mantissa of scientific notation.
	while(ftob_tmp > 0.0L && ftob_tmp < 1.0L) {
		ftob_tmp *= base;
		j++;
	}
	while(ftob_tmp >= base) {
		ftob_tmp /= base;
		j--;
	}
	//reinitialise
	ftob_tmp = sign * ld;
	ftob_tmp *= powl(base, (j - 1));
	k = i + 1;

	//main loop
	for(n_digits += i; i < n_digits; i++) {
		if(i == k)
			str[n_digits++, i] = '.';
		else {
			str[i] = (int)fmod((ftob_tmp * powl(base, index++)), base);
			str[i] += (str[i] < 10) ? '0' : 'A' - 10;
		}
	}

	//write exponent
	(base <= 14) ? (str[i++] = 'E') : (str[i++] = '\\', str[i++] = 'E');
	str[i++] = (j > 0) ? '-' : '+';
	str[i++] = '0';
	str[i] = '0';
	if(j != 0) {
		(j < 0) ? (j *= -1) : 0;
		for(k = j, --i; k / base != 0; k /= base)
			i++;
		str[++i] = '\0';
		do {
			str[--i] = ((k = j % base) < 10) ? k + '0' : k + 'A' - 10;
			j /= base;
		} while(j != 0);
	}
	else
		str[++i] = '\0';

	return str;
}
/* Base is between 2-36.
 * Argument 'n_digits' must be lesser then size of str.
 * the string is only precise for DBL_MANT_DIG * log(2) * log(base) digits, in base (about 15 digits in decimal).
 */
