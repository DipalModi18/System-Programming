#include<stdio.h>

int main()
{
int ar[4] = {5, 10, 15, 20};
int *ptr;

// Method 1:
for(int i=0; i<4; i++)
	printf("%d ", ar[i]);

ptr = ar; // Pointer and arrays are interchangeable
// ptr = ar is equivalent to ptr = &ar[0]
// Cannot do ar = ptr as name of the array is a constant pointer

// Method 2:
for(int i=0; i<4; i++)
	printf("%d ", ptr[i]);

// Method 3:
for(int i=0; i<4; i++)
	printf("%d ", *(ptr + i));

// Method 4:
for(int i=0; i<4; i++)
	printf("%d ", *(ar + i));
}
