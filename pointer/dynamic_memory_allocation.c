#include<stdio.h>
#include<stdlib.h>

int main()
{
int *ptr1;
float *ptr2;

ptr1 = malloc(sizeof(int)); // Allocate space for an integer
ptr2 = malloc(sizeof(float)); // Allocate space for a float

*ptr1 = 20; // assigning values to the new memory
*ptr2 = 13.5;

free(ptr1); // free previously allocated space
free(ptr2);
}
