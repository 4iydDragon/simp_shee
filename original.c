#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

int main() {
    char command[MAX_COMMAND_LENGTH];
    pid_t pid;

    while (1) {
        printf("Shell > ");

        if (fgets(command, sizeof(command), stdin) == NULL) {
            printf("\n");
            break;  /* End of file (Ctrl+D) detected */
        }

        /* Remove the newline character from the command */
        command[strcspn(command, "\n")] = '\0';

        /* Fork a child process */
        pid = fork();

        if (pid < 0) {
            /* Forking failed */
            fprintf(stderr, "Failed to fork\n");
            continue;
        }
        else if (pid == 0) {
            /* Child process */
            execlp(command, command, (char*) NULL);

            /* If the above line is executed, it means the executable was not found */
            fprintf(stderr, "Command not found: %s\n", command);
            exit(1);
        }
        else {
            /* Parent process */
            int status;
            waitpid(pid, &status, 0);

            if (WIFEXITED(status) && WEXITSTATUS(status) == 1) {
                fprintf(stderr, "Command execution failed: %s\n", command);
            }
        }
    }

    return 0;
}
