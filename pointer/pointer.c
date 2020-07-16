#include<stdio.h>

int main()
{
int n = 10;
int *ptr = &n;  // ptr is initialized to address of n

printf("%d %d %d \n", n, *ptr, ptr[0]);

ptr[0] = 20;

// C assumes all the time that a pointer is pointing to an array
 // The programmer is responsible for the interpretation
ptr[1] = 30;  // Equivalent to *(ptr + 1*sizeof(int)) = 20

ptr++;
*ptr = 30;  // Error not detected at compilation time
// Segmentation fault at runtime
}
