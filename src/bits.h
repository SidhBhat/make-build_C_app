/* Header file containing declarations of functions in "bits.c"
 */

#ifndef BITS_H_INCLUDED
#define BITS_H_INCLUDED 1

#include<stddef.h>
#include<sys/ioctl.h>

#define PLOTMEM_V_MIN_WITDH 45
#define PLOTMEM_V_MAX_WITDH (size) ((size) * 16 + 16) // size is the size of memory to be printed in bytes.

extern struct winsize w;

// plotMem_h: plot the data in *ptr upto 'size' in horizontal rows
void plotMem_h(const size_t size, void const *const ptr);

// plotMem_v: plot the data in *ptr upto 'size' in vertical columns
void plotMem_v(const size_t size, const void*const ptr);

/*prints the binary value stored in adress 'ptr' upto the size (in bytes).*/
void printBits(const size_t size, const void*const ptr);

// Set the binary value stored in adress 'ptr' upto the size (in bytes), in string str.
void getBits(size_t const size, void const *const ptr, char *str);

// Write the binary string in bits, to address '*var' upto size(in bytes).
void SetBits(size_t size, void *const var, char const *const bits);
/* The string is read left-right.
 * For a string larger then size, (size * 8 bits) only the first 'size * 8' bits are taken into account.
 * For a string smaller then size (size * 8 bits), bits are filled from the right, with the leftmost bit as the most significant.
 * Any other character other than '1' or '0' terminates the string.
 * A null/zero string is interpreted as 0.
 */

// Write the binary string in bits, to address '*var' upto size(in bytes).
void SetBits_v2(size_t size, void *const var, char const *const bits);
/* The string is read left-right.
 * For a string larger then size, (size * 8 bits) only the first 'size * 8' bits are taken into account.
 * A quirk of this version is that strings smaller than 'size * 8' are not accepted.
 * Any other character other than '1' or '0' terminates the string.
 */

/* Reurns the intger value of the input binary string.*/
int setBits(char const * const bits);
/* The string is read left-right.
 * The leftmost bits are filled first, therfore for a sring longer then 32 bits(sizeof int) only the first 32 bits(sizeof int) from the leftmost side is taken.
 * For a string containing char that are not '1' or '0', the return value is the value of the binary string before the first non '1' or '0' char.
 * If first char is a non '1'or '0' char then the return value is 0.
 */

/*if p is position from zero, setbits takes n bits from var y (starting zero), and places it at position p in x the remaing bits unchanged*/
int changebits(int x, unsigned short int p, unsigned short int n, int y);

//if p is position from zero, invertbits inverts (takes the compliment of) n bits from p and leaves the rest unchanged
int invertbits(int x, unsigned short int p, unsigned short int n);

//rightrotbits rotates the bits tn x to the right by n. (this means moving every bit on the left to the right by n, and filling the blanks on the right by bit that have fallen of the left border)
int rightrotbits(int x, unsigned short int n);

//counts the nber of bits that have value 1 in var x.
int Bitcount(int x);

#endif /* "bits.h" */
