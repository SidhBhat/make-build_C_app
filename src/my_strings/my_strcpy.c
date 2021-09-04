/* copy: Copy from into to: assume to is big enough */
void my_strcpy(const char *from, char *to)
{
	int i;

	i = 0;
	while ((to[i] = from[i]) != '\0')
		++i;
}
