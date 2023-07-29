#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024

void read_input(char *input) {
    printf("Shell> ");
    fgets(input, MAX_INPUT_LENGTH, stdin);

    // Remove the newline character from the input
    input[strcspn(input, "\n")] = '\0';
}

int execute_command(char *command) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        char *args[64];
        char *token;

        // Split the command into tokens
        int i = 0;
        token = strtok(command, " ");
        while (token != NULL) {
            args[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        args[i] = NULL;

        // Execute the command
        if (execvp(args[0], args) < 0) {
            perror("Execution failed");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        waitpid(pid, &status, 0);
    }
    return 1;
}

int main() {
    char input[MAX_INPUT_LENGTH];

    while (1) {
        read_input(input);

        // Exit the shell if the user inputs "exit"
        if (strcmp(input, "exit") == 0) {
            break;
        }

        // Execute the command
        if (execute_command(input) == 0) {
            break;
        }
    }

    return 0;
}
