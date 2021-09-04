/* getescseq : function to interpret escape sequences in input string and place the character in output
* Assuming out[] is at least one fourth of in[].
*/
void setescsqu(const char *in, char *out)
{
	int i, j, k;

	//Initialisation of out[]
	for(i = 0; in[i] != '\0'; i++)
		;
	for(j = 0; j <= i / 4; j++)
		out[j] = '\0';

	for(i = j = 0; in[i] != '\0'; i++) {
		if(in[i] == '\\')
			switch (in[++i]) {
				case 'n':
					out[j++] = '\n';
					break;
				case 't':
					out[j++] = '\t';
					break;
				case 'v':
					out[j++] = '\v';
					break;
				case 'b':
					out[j++] = '\b';
					break;
				case 'r':
					out[j++] = '\r';
					break;
				case '\\':
					out[j++] = '\\';
					break;
				case '\'':
					out[j++] = '\'';
					break;
				case '\"':
					out[j++] = '\"';
					break;
				case 'x':
					out[j] = 0; // initialise to zero
					for(k = 0; k < 2; k++)
						if(in[i + 1] >= 'a' && in[i + 1] <= 'f')
							out[j] = out[j] * 16 + 10 + in[++i] - 'a';
						else if(in[i + 1] >= 'A' && in[i + 1] <= 'F')
							out[j] = out[j] * 16 + 10 + in[++i] - 'A';
						else if(in[i + 1] >= '0' && in[i + 1] <= '9')
							out[j] = out[j] * 16 + in[++i] - '0';
						else if(k == 0)
							out[j] = in[--i]; //if first character is invalid, return to location of '\'

					j++;// increment
					break;
				case '0': case '1': case '2': case '3':
				case '4': case '5': case '6': case '7':
					out[j] = 0;
					for(--i, k = 0; k < 3; k++)
						if(in[i + 1] >= '0' && in[i + 1] < '8')
							out[j] = out[j] * 8 + in[++i] - '0';
						else if(k == 0)
							out[j] = in[--i]; //if first character is invalid, return to location of '\'

					j++;// increment
					break;
				default:
					out[j++] = in[--i];
					break;
			}
		else if((in[i] >= 32 && in[i] < 127) || (in[i] >= 8 && in[i] < 11))
			out[j++] = in[i];

	}
	//terminate outstring
	out[j] = '\0';

}
