// expandstr : expand sequences of the sort a-z from input string to output string.
void expandstr(const char *in, char *out)
{
	int i, j, k;

	for(i = j = 0; in[i] != '\0'; i++) {
		if(i > 0 && in[i] == '-' && in[i + 1] != '\0' && in[i + 1] != '\n') {
			if(in[i + 1] == '-') {
				if(in[++i + 1] == '-') {
					out[j++] = in[++i];
					continue;
				}
				else
					j++;
			}
			for(k = in[i - 1], j--; k != in[i + 1]; (in[i - 1] < in[i + 1]) ? k++ : k--)
				out[j++] = k;
		}
		else
			out[j++] = in[i];
	}
	//terminate string
	out[j] = '\0';
}
/* Notes:
 * Sequences are expanded by writing all characters between the left and right of a '-' character.
 * In two consecutive '-', the leading '-' is interpreted literally.
 * The sequence "---" will right a single '-' character.
*/
