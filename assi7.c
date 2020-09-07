#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


int main() {
    while(1) {
        char cmd[256];      // to store the command
        char * cmd_arg[120];   // to separate the arguments from the command in array | could not find vector in c
        char * exit_literal = "exit\n"; // to check exit condition
        char * args;        // to fetch arguments from the argument list

        printf("\n\nEnter Command > ");

        if(fgets(cmd, sizeof(cmd), stdin) == NULL) {
            // On Linux, Ctrl + D generates EOF, When EOF is encountered, fgets() returns a null pointer
            printf("\nBye Bye\n");
            break;  // Terminate the shell
        }

        // if user enters exit the program prints Bye Bye and terminates
        if(strcmp(cmd, exit_literal) == 0) {
            printf("Bye Bye \n");
            break;
        }

        int number_of_commands = 0;
        char * commands[10];    // commands separated by ; are stored in the array: Max upto 10 command per line seperated by ;
        commands[number_of_commands] = (char *) malloc(50 * sizeof(char));  // allocate memory for the commands
        int counter = 0;

        for(int i = 0; i < strlen(cmd); i++) {          // Loop and find all the commands seperated by semicolon; store them in commands
            if(cmd[i] == ';') {
                commands[number_of_commands][counter] = '\0';  // Current command ended so store end delimiter '\0'
                counter = 0;
                number_of_commands++;
                commands[number_of_commands] = (char *) malloc(50 * sizeof(char));  // Assign memory for the new command
            } else {
                commands[number_of_commands][counter] = command[i];  // Character by character store the command in commands variable
                counter++;
            }
        }

        commands[number_of_commands][counter] = '\0';  // End of command for the last command
        counter = 0;
        number_of_commands++;

        int number_of_arguments = 0;

        for(int i = 0; i < number_of_commands; i++) {
            printf("\nNext Command: %s\n", commands[i]);
            number_of_arguments = 0;

            // separating arguments with delimiter " " space using strtok
            for (args = strtok(commands[i], " "); args; args = strtok(NULL, " ")) {
                cmd_args[number_of_arguments] = args;
                number_of_arguments++;
            }

	    // Store arguments in arguments var
            char * arguments[number_of_arguments + 1];
            for(int j = 0; j < number_of_arguments; j++) {
                arguments[j] = cmd_args[j];
            }

            arguments[number_of_arguments] = NULL;

            if(arguments[number_of_arguments-1][strlen(arguments[number_of_arguments-1]) - 1] == '\n') {
                arguments[number_of_arguments-1][strlen(arguments[number_of_arguments-1]) - 1] = '\0';
            }

	    pid_t pid;
            if((pid=fork()) == 0) {                  // child process
                execvp(arguments[0], arguments);
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
