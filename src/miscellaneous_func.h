#ifndef MISCELLANEOUS_FUNC_H_INCLUDED
#define MISCELLANEOUS_FUNC_H_INCLUDED 1

// function to round 'input' to nearest integer
int Int_Round(float input);

//asuming aschii , converts capital alphbet to lover case
char lower(char ch);

// Converts celcius temprature to farhenhiet
float CelsiusToFahr(float celsius);

// digitcount : Counts the number of digits in 'num' if it were written in the Hindu-Araibic nummeral system, with arithmetic base 'base'.
unsigned short digitcount(long long num, unsigned short base);

#endif /* "miscellaneous_func.c" */
