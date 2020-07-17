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



// dynamic array
ptr2 = malloc(5 * sizeof(float)); // pointer can be assigned different memory address
// name of a declared array is a constant but not the name of the dynamic array
if(ptr2 == NULL)
{
	printf("Unable to allocate memory for the array");
	exit(0);
}
for(int i=0; i<5; i++)
{
	scanf("%f", &ptr2[i]);
	printf("%f\n", ptr2[i]);
}

free(ptr1); // free previously allocated space
free(ptr2);
}
