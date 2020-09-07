#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>


void childFunction(char *line, int lineSize)
{
	// Reference: https://www.tutorialspoint.com/learn_c_by_examples/program_to_reverse_line_in_c.htm
	// int j = sizeof(line) - 1, i=0;
	int j = lineSize - 1, i=0;
	char ch;
	// printf("Size of line: %d || line: %s\n", j, line);

	while(i<j)
	{
		ch = line[j];
		line[j] = line[i];
		line[i] = ch;
		i++;
		j--;
	}
	printf("Reversed string: %s\n", line);
	// TODO: Store the output in codes.txt file
}

int main()
{
	int pid, status, p;
	size_t lineSize = 0;
	char *line;

	printf("This program encodes text\n");

	while(1)
	{
		printf("\n\n\nEnter a sentence: ");

		// TODO: Replace below to line to read input from the console using the read() system call
		// line = (char *)malloc(lineSize * sizeof(char));
		lineSize = getline(&line, &lineSize, stdin);  // fd = 0 to read from console

		printf("Input line: %s || Line size: %d\n", line, lineSize);
		pid = fork();

		if(pid > 0)	// Parent Process
		{
			printf("Created a child to perform task, waiting...\n");
			p = wait(&status);
			if(WIFEXITED(status))
			{
				printf("Normal termination of child with status: %d\n", WEXITSTATUS(status));
				if(WEXITSTATUS(status) == 10)
				{
					printf("Empty line\n");
				}
				// TODO: Read the reversed string from the codes.txt file
			}
			else
			{
				printf("Abnormal termination of child\n");
			}
		}
		else  		// Child Process
		{
			printf("I am child working for my parent\n");
			if(lineSize == 1) // i.e. the line contains \n character only
				exit(10);
			childFunction(line, (int)lineSize);
		}
	}


	exit(0);
}
