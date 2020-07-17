#include<stdio.h>
#include<stdarg.h>

int total(int n, ...)
{
	va_list arg_list;
	int sum = 0, v;

	// create arg_list for the n arguments
	va_start(arg_list, n);

	// extract all arguments from arg_list
	for(int i=0; i<n; i++)
	{
		v = va_arg(arg_list, int);
		printf("%d\n", sum);
		sum += v;
	}

	va_end(arg_list);
	return sum;
}

int main()
{
printf("sum: %d\n", total(3, 2, 3, 5));
return 0;
}
