#include<stddef.h>
#include<string.h>
#include<math.h>

// ftob : convert a long double value to a character representation in string str, with arithmetic base 'base'.
char *ftob(long double ld, char *str, unsigned short int n_digits, unsigned short int base)
{
	long double ftob_tmp;
	short unsigned index = 1;
	short int i = 0, j = 0 , k = 0;
	short const sign = (signbit(ld)) ? -1 : 1;

	//check base, number.
	if(base < 2 || base > 36)
		return NULL;
	else if(ld == INFINITY)
		return strcpy(str, "inf");
	else if(ld == -INFINITY)
		return strcpy(str, "-inf");
	else if(__isnanl(ld))
		return strcpy(str, "nan");
	//initialisations
	(sign == -1) ? str[i++] = '-' : 0;
	ftob_tmp = sign * ld;
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
	if(ftob_tmp >= 0.0L && ftob_tmp < 1.0L) {
		str[i++] = '0';
		str[i++] = '.';
		for(k = 0; k < j - 1 && k < n_digits - 1; k++)
			str[i++] = '0';
		n_digits -= j;
	}
	else if(ftob_tmp >= base)
		k = i - j + 1;
	else
		k = i + 1;
	ftob_tmp *= powl(base, --j);

	//main loop
	for(n_digits += i; i < n_digits; i++) {
		if(i == k)
			str[n_digits++, i] = '.';
		else {
			str[i] = (int)fmod((ftob_tmp * powl(base, index++)), base);
			str[i] += (str[i] < 10) ? '0' : 'A' - 10;
		}
	}

	//finalise
	str[i] = '\0';

	return str;
}
/* Base is between 2-36.
 * Argument 'n_digits' must be lesser then size of str.
 * the string is only precise for DBL_MANT_DIG * log(2) * log(base) digits, in base (about 15 digits in decimal).
 */
