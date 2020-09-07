#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


int main() {
    while(1) {  // Infinite loop will break on CTRL + D or when user enters exit
        char cmd[256];      // to store the command

        printf("\n\nEnter Command > ");

        if(fgets(cmd, sizeof(cmd), stdin) == NULL) {
            // On Linux, Ctrl + D generates EOF, When EOF is encountered, fgets() returns a null pointer
            printf("\nBye Bye\n");
            break;  // Terminate the shell
        }

        // if user enters exit the program prints Bye Bye and terminates
        if(strcmp(cmd, "exit\n") == 0) {
            printf("Bye Bye \n");
            break;
        }

        int cmd_count = 0;
        char * cmds[10];    // commands separated by ; are stored in the array: Max upto 10 command per line seperated by ;
        cmds[cmd_count] = (char *) malloc(50 * sizeof(char));  // allocate memory for the commands
        int counter = 0;

        for(int i = 0; i < strlen(cmd); i++) {          // Loop and find all the commands seperated by semicolon; store them in commands
            if(cmd[i] == ';') {
                cmds[cmd_count][counter] = '\0';  // Current command ended so store end delimiter '\0'
                counter = 0;
                cmd_count++;
                cmds[cmd_count] = (char *) malloc(50 * sizeof(char));  // Assign memory for the new command
            } else {
                cmds[cmd_count][counter] = cmd[i];  // Character by character store the command in commands variable
                counter++;
            }
        }

        cmds[cmd_count][counter] = '\0';  // End of command for the last command
        counter = 0;
        cmd_count++;

        int arg_count = 0;
        char * cmd_args[120];   // to separate the arguments from the command in array | could not find vector in c
        char * args;        // to fetch arguments from the argument list
        for(int i = 0; i < cmd_count; i++) {
            printf("\nNext Command: %s\n", cmds[i]);
            arg_count = 0;

            // separating arguments with delimiter " " space using strtok
            for (args = strtok(cmds[i], " "); args; args = strtok(NULL, " ")) {
                cmd_args[arg_count] = args;
                arg_count++;
            }

	    // Store arguments in arguments var
            char * args[arg_count + 1];
            for(int j = 0; j < arg_count; j++) {
                args[j] = cmd_args[j];
            }

            args[arg_count] = NULL;

            if(args[arg_count-1][strlen(args[arg_count-1]) - 1] == '\n') {
                args[arg_count-1][strlen(args[arg_count-1]) - 1] = '\0';
            }

	    pid_t pid;
            if((pid=fork()) == 0) {                  // child process
                execvp(args[0], args);
                exit(0); // return the finish status
            } else {                  // parent process
                int status;
                wait(&status);  // wait for the child process to complete
                printf("Child %d terminated with status %d\n", pid, WEXITSTATUS(status));   // print the necessary information
            }
        }
    }
    return 0;
}
