#ifndef MY_STRINGS_H_INCLUDED
#define MY_STRINGS_H_INCLUDED 1

// function to compare srings s & t and and remove from s the characters appearing in t
void strsqueeze(char *str, const char *t);

// function to conpare s1 and s2, and return the position (as pionter to array) to the first location in s1 where any character from s2 ocurrs (order of chars in s2 does not matter)
char *my_strpbrk(const char *str1 , const char *str2);

// function returns a pointer to the first location where the string 'pattern' ocurrs in string str
char *my_strstr(const char *str, const char *pattern);

// function returns a pointer to the rightmost location where the string 'pattern' ocurrs in string str
char *my_strstr_v2(const char *str, const char *pattern);

//returns the length of the the string str. '\0' arks end of string
unsigned int my_strlen(const char *str);

/*RemoveBlanks: removes trailing blanks and tabs from a line , returns the number of trailing blanks*/
unsigned int RemoveBlanks(char *line , unsigned int lim);

/* getstr: read a string into s, return length */
unsigned int getstr(char *str, unsigned int lim);

/* GetLine: read a line into s, return length */
unsigned int Getline (char *line , unsigned int lim);

/*strreverse: reverses a line*/
void strreverse(char *line , unsigned int lim);

// expandstr : expand squences of the sort a-z from input string to output string.
void expandstr(const char *in, char *out);
/* Notes:
 * Squences are expanded by writing all characters between the left and right of a '-' character.
 * In two consecutive '-', the leading '-' is interpreted literally.
 * The squence "---" will right a single '-' character.
*/

/* copy: Copy from into to: assume to is big enough */
void my_strcpy(const char *from, char *to);

/* getescseq : Function to replace appropriate escape squence in output string for invisible characters in input string.
* Assuming out[] is at least four time big then in[].
*/
void getescseq(const char *in, char *out);

/* getescseq : function to interprete escape sequences in input string and place the character in output
* Assuming out[] is at least four time big then in[].
*/
void setescsqu(const char *in, char *out);

#endif // "my_strings.h" included
