/*strreverse: reverses a line*/
void strreverse(char *line ,unsigned int lim)
{
	int i;
	char ch;

	for(i = 0 ; i < lim - 1 ; i++)
		if(line[i] == '\0')
		{
			lim = i;
			while(lim > 0)
			{
				ch = line[--lim];
				if(lim >= i - lim - 1)
				{
					line[lim] = line[i - lim - 1];
					line[i - lim - 1] = ch;
				}
			}
		}
}
