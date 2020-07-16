#include<stdio.h>

void *myFunction() // A function that returns a generic pointer
{
	void *ptr;
	return ptr;
}

int main()
{
// A void pointer is a pointer that has no associated data type with it.
// A void pointer can hold address of any type and can be typcasted to any type.
int *ptr1;
float *ptr2;

ptr1 = myFunction(); // void * is casted to int*
ptr2 = myFunction(); // void * is casted to float*


int a = 10;
char b = 'x';
void *p = &a;
p = &b;  // Same void pointer p is holding address of char


// void pointer cannot be dereferenced
int c = 10;
void *ptr = &c;
// printf("%d", *ptr); // Error
printf("%d\n", *(int *)ptr);
}
