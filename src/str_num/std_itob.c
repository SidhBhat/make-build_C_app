//iotb : convert x to characters in str[], with the arithmetic base 'base'.
char *itob(long long int x, char *str, unsigned short int base);
//iotbw : convert x to characters in str[], with the arithmetic base 'base'. Right adjust to width
char *itobw(long long int x, char* str, unsigned short int base, short unsigned int width);


#define BASE 10U

//itod : convert x to characters in str[]. Returns pointer to str.
char *itod(long long int x, char *str)
{
	return itob(x, str, BASE);
}

//itodw : convert x to characters in str[].  Returns pointer to str. Right adjust to width
char *itodw(long long int x, char *str, short unsigned int width)
{
	return itobw(x, str, BASE, width);
}

#undef BASE
#define BASE 16U

//itoh : convert x to hex characters in str[]. Returns pointer to str.
char *itoh(long long int x, char *str)
{
	return itob(x, str, BASE);
}

//itohw : convert x to hex characters in str[]. Returns pointer to str. Right adjust to width
char *itohw(long long int x, char *str, short unsigned int width)
{
	return itobw(x, str, BASE, width);
}

#undef BASE
#define BASE 8U

//itooct : convert x to octal characters in str[]. Returns pointer to str.
char *itooct(long long int x, char *str)
{
	return itob(x, str, BASE);
}

//itooctw : convert x to octal characters in str[]. Returns pointer to str. Right adjust to width
char *itooctw(long long int x, char *str, short unsigned int width)
{
	return itobw(x, str, BASE, width);
}

#undef BASE
#define BASE 2U

//itobin : convert x to binary characters in str[]. Returns pointer to str. Returns pointer to str.
char *itobin(long long int x, char *str)
{
	return itob(x, str, BASE);
}

//itobinw : convert x to binary characters in str[]. Returns pointer to str. Right adjust to width
char* itobinw(long long int x, char* str, short unsigned int width)
{
	return itobw(x, str, BASE, width);
}

#undef BASE
