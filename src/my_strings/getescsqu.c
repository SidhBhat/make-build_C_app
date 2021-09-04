/* getescseq : Function to replace appropriate escape sequence in output string for invisible characters in input string.
* Assuming out[] is at least four time bigger then in[].
*/
void getescseq(const char *in, char *out)
{
	const char defescsqu[] = {'\n', '\t', '\v', '\b', '\r'};
	const char escsqu[] = "\\n\\t\\v\\b\\r";
	int i, j, k, qu, re;

	//Initialisation of out[]
	for(i = 0 ; in[i] != '\0' ; i++)
		;
	for(j = 0 ; j < 4 * i ; j++)
		out[j] = '\0';

	//Main loop
	for(i = j = 0 ; in[i] != '\0' ; i++) {
		qu = 1;
		k = 0;
		while(k < sizeof(defescsqu) / sizeof(defescsqu[0]))
			if(in[i] == defescsqu[k++]) {
				out[j++] = escsqu[2 * k - 2];
				out[j++] = escsqu[2 * k - 1];
				qu = 0;
			}

		if(in[i] >= 32 && in[i] < 127)
			out[j++] = in[i];
		else if(qu) {
			qu = re = (unsigned char)in[i]; // Initialisation if qe,re to the array member
			out[j++] = '\\';
			out[j++] = 'x';
			//seek two steps forward and write digit starting from 'Least Significant Digit'
			for(j += 1 ; out[j] != 'x' ; j--) {
				qu /= 16;
				if((re %= 16) < 10)
					out[j] = '0' + re;
				else
					out[j] = '0' + re + 'A' - '9' - 1;
				re = qu;
			}
			j += 3;//seek back to position for next char
		}
	}
	//terminate outstring
	out[j] = '\0';
}
