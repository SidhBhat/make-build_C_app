// function to compare strings s & t and and remove from s the characters appearing in t
void strsqueeze(char *str, const char *t)
{
	int i, j, k;
	for (k = 0; t[k] != '\0'; k++)
	{
		for (i = j = 0; str[i] != '\0'; i++)
			if (str[i] != t[k])
				str[j++] = str[i];
		str[j] = '\0';
	}
}
