#include<stddef.h>

//iotbw : convert x to characters in str[], with the arithmetic base 'base'. Right adjust to width
char *itobw(long long int x, char* str, unsigned short int base, short unsigned int width)
{
	long long itob_tmp;
	short sign;
	short i;

	//check invalid base
	if(base < 2 || base > 36) {
		str[0] = '\0';
		return NULL;
	}
	//initialisations
	sign = (x < 0) ? -1 : 1;
	itob_tmp = x;
	for(i = 1; (itob_tmp /= (sign * base)) != 0; i++)
		;
	if(sign == -1)
		i++;

	//main loop
	itob_tmp = i;
	(width > i) ? (str[i = width] = '\0') : (str[i] = '\0');
	for(--i; i >= 0; i--) {
		if(i < width - itob_tmp)
			str[i] = ' ';
		else if(i == width - itob_tmp && sign == -1)
			str[i] = '-';
		else if(i == 0 && sign == -1)
			str[i] = '-';
		else {
			if(sign * (x % base) < 10)
				str[i] = sign * (x % base) + '0';
			else
				str[i] = sign * (x % base) + 'A' - 10;
			x /= base;
		}
	}

	return str;
}
/* base is a number between 2-36, any other value in base will make str a zero string and exit*/
