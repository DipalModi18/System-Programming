#include<stdio.h>
#include<stdlib.h>

// If argv provided then contents of file argv[1] will be printed
 // i.e. redirected on the stdout otherwise whatever written on the stdin will be sent to stdout
int main(int argc, char *argv[])
{
FILE *fd;
char c;

if(argc == 1)
	fd = stdin;
else
	if( (fd = fopen(argv[1], "r")) == NULL)
	{
		fprintf(stderr, "Cannot open %s\n", argv[1]);
		exit(0);
	}

while( (c=getc(fd)) != EOF)
	putc(c, stdout);

exit(0);
}
