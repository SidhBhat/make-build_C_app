//btoi : convert a string representing a number with arithmetic base 'base', to it's integral value and return it.
long long int btoi(char const *num_str, unsigned short int base);

#define BASE 10U

/*dtoi : converts a string, to it's  integer value and returns it*/
long long int dtoi(char* str)
{
	return btoi(str, BASE);
}
//behavior with string handling is identical to btoi.

#undef BASE
#define BASE 16U

/*htoi : converts a hex string, to it's  integer value and returns it*/
long long int htoi(char* str)
{
	return btoi(str, BASE);
}
//behavior with string handling is identical to btoi.

#undef BASE
#define BASE 8U

/*octtoi : converts a octal string, to it's  integer value and returns it*/
long long int octtoi(char* str)
{
	return btoi(str, BASE);
}
//behavior with string handling is identical to btoi.

#undef BASE
#define BASE 2U

/*bintoi : converts a binary string, to it's  integer value and returns it*/
long long int bintoi(char* str)
{
	return btoi(str, BASE);
}
//behavior with string handling is identical to btoi.

#undef BASE
