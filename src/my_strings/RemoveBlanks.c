/*RemoveBlanks: removes trailing blanks and tabs from a line , returns the number of trailing blanks*/
unsigned int RemoveBlanks(char *line , unsigned int lim)
{
	int i;

	for(i = 0 ; i < lim - 1 ; i++ )
		if(line[i] == '\0')
		{
			lim = i;
			while(line[lim - 1] == ' ' || line[lim - 1] == '\t' ||  line[lim - 1] == '\n' )
				if(lim - 1 >= 0)
					line[lim-- - 1] = '\0';
		}

	return i - lim - 1;
}
