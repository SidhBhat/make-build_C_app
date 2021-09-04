//Sort the values in 'data' in descending order. Version of sorting by D .L Shell.
void Sort_Descend(int *data, unsigned int lim) // much more efficient and fasrter
{
	int i, j, tmp, gap;

	for(gap = lim / 2 ; gap > 0 ; gap /= 2) {
		for(i = gap ; i < lim ; i++)
			for(j = i - gap ; j >= 0 && data[j] > data[j + gap] ; j -= gap) {
				tmp = data[j];
				data[j] = data[j + gap];
				data[j + gap] = tmp;
			}
	}
}
