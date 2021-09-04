// search exhaustively for value x in array 'data'
int search(int x, int *data, unsigned int lim)
{
	int i;

	for(i =  0 ; i < lim - 1 ; i++)
		if(data[i] == x)
			return i;

	return -1;
}
