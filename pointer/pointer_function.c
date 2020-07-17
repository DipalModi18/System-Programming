#include<stdio.h>

int square(int x)
{
	return x * x;
}

int cube(int x)
{
	return x*x*x;
}

int calculate(int (*func_ptr)(int), int x)
{
	// Passing function as parameter
	return func_ptr(x);
}

int main()
{
int (*func_ptr)(int); // pointer to a function whose argument and return type is int

func_ptr = square;
printf("Square: %d OR %d\n", func_ptr(10), calculate(square, 10));

func_ptr = cube;
printf("Cube: %d OR %d \n", func_ptr(10), calculate(cube, 10));
}
