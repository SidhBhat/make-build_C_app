//Sort the values in 'data' in ascending order. Version of sorting by D .L Shell.
void Sort_Ascend(int *data, unsigned int lim);

//search using binary search methode for value x in array 'data'
int binsearch(int x, int *data, unsigned int lim)
{
	int min, mid, max;

	Sort_Ascend(data, lim);
	min = 0;
	max = lim - 1;
	mid = max + min / 2;

	while(min <= max) {
		mid = (min + max) / 2;

		if(x <= data[mid])
			max = mid - 1;
		else
			min = mid + 1;
	}

	if (x > data[mid])
		++mid;
	else if (x < data[mid])
		--mid;

	if(x == data[mid])
		return mid;
	else
		return -1;
}
/* dependancies :
 * function : void Sort_Ascend(int [], int)
 */
