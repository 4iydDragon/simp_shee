#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

int main() {
    char command[MAX_COMMAND_LENGTH];
    char* arguments[MAX_ARGUMENTS];
    pid_t pid;
    int num_arguments = 0;

    while (1) {
        printf("#cisfun$ ");

        if (fgets(command, sizeof(command), stdin) == NULL) {
            printf("\n");
            break;  /* End of file (Ctrl+D) detected */
        }

        /* Remove the newline character from the command */
        command[strcspn(command, "\n")] = '\0';

        /* Check if the command is an absolute path */
        if (command[0] != '/') {
            fprintf(stderr, "./shell: No such file or directory\n");
            continue;
        }

        /* Tokenize the command line */
        arguments[num_arguments] = strtok(command, " ");

        while (arguments[num_arguments] != NULL && num_arguments < MAX_ARGUMENTS - 1) {
            num_arguments++;
            arguments[num_arguments] = strtok(NULL, " ");
        }

        arguments[num_arguments] = NULL; /* Set the last element to NULL for exec functions*/

        /* Fork a child process */
        pid = fork();

        if (pid < 0) {
            /* Forking failed */
            fprintf(stderr, "Failed to fork\n");
            continue;
        } else if (pid == 0) {
            /* Child process */
            execvp(arguments[0], arguments);

            /* If the above line is executed, it means the executable was not found */
            fprintf(stderr, "./shell: No such file or directory\n");
            exit(1);
        } else {
            /* Parent process */
            int status;
            waitpid(pid, &status, 0);

            if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                fprintf(stderr, "./shell: Error executing command\n");
            }
        }
    }

    return 0;
}
