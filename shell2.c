#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024

void print_prompt() {
    printf("Shell> ");
}

void read_input(char *input) {
    fgets(input, MAX_INPUT_LENGTH, stdin);

    // Remove the newline character from the input
    input[strcspn(input, "\n")] = '\0';
}

void execute_command(char *command, char *program_name) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0) {
        perror(program_name);
        return;
    } else if (pid == 0) {
        // Child process
        if (execlp(command, command, (char *)NULL) < 0) {
            perror(program_name);
            _exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        waitpid(pid, &status, 0);
    }
}

int main(int argc, char *argv[]) {
    char input[MAX_INPUT_LENGTH];

    while (1) {
        print_prompt();
        read_input(input);

        // Exit the shell if the user inputs "exit" or encounters end of file (Ctrl+D)
        if (strcmp(input, "exit") == 0 || feof(stdin)) {
            break;
        }

        // Execute the command
        execute_command(input, argv[0]);
    }

    return 0;
}
