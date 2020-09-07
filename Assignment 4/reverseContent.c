#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int reverseContents(char *inputFile, char *outputFile)
{
	char buffer[512], c;
	long int fileSize, position;
	FILE *fd1, *fd2;

	fd1 = fopen(inputFile, "r");  // Open the input file in read only mode
	fd2 = fopen(outputFile, "w");  // Open the output file in write mode


	for(int i=0; i<3; i++)  // Reads header from the fd1 and writes to the fd2
	{
		// Header contains:
		// First line: P2 or P5 --> P2 means data in ascii format, P5 implies binary format
		// Second line: 512 512 --> Width and height
		// 255: Unique values of a pixel --> 255 implies a pixel = 8 bit
		fgets(buffer, 512, fd1);
		fputs(buffer, fd2);
	}

	fseek(fd1, 0, SEEK_END); // Set fd1 pointer to the end of file
	fileSize = ftell(fd1);
	position = fileSize;

	while(position--)
	{
		fseek(fd1, position-fileSize, SEEK_END);
		c = fgetc(fd1);
		fputc(c, fd2);
		if(position == 15) break;
	}
}

int main()
{
	char *inputFile="m1.pgm", *outputFile="m2.pgm";
	reverseContents(inputFile, outputFile);
	printf("\n File contents of %s reversed and stored in %s\n", inputFile, outputFile);
}
