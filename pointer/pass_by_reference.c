#include<stdio.h>

int divide(int a, int b, int *res)
{
	if(b==0)
		return 0;
	else
		*res = a/b;
return 1;
}

int main()
{
int a, b, res;
int *ptr=&res;

divide(4, 2, &res);
printf("%d\n", res);

divide(9, 3, ptr);
printf("%d\n", *ptr);
}
