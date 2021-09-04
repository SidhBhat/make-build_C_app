#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED 1

//Sort the values in 'data' in ascending order
void Sort_Ascend(int *data, unsigned int lim);

//Sort the values in 'data' in descending order
void Sort_Descend(int *data, unsigned int lim);

// search exhaustivley for value x in array 'data'
int search(int x, int *data, unsigned int lim);

//search using binary search methode for value x in array 'data'
int binsearch_V2(int x, int *data, unsigned int lim);
/* dependancies :
 * function : void Sort_Ascend(int [], int)
 */

#endif /* "data.h" included */
