// returns the length of the the string str. '\0' arks end of string
unsigned int my_strlen(const char* str)
{
	unsigned int i;

	for(i = 0; str[i] != '\0'; i++)
		;

	return i;
}
