#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
// Get the process ID
printf("Hello, My PID is %d\n", getpid());

// Get the parent process ID
printf("Hello, My PPID is %d\n", getppid());

// The process can obtain its uid using the system call getuid()
printf("User ID: %d\n", getuid());

exit(0);
}
