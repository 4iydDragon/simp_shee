#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>

#define MAX_COMMAND_LENGTH 100

int main(void) {
    char command[MAX_COMMAND_LENGTH];
    pid_t pid;
    bool interactive_mode = isatty(fileno(stdin));

    while (1) {
        if (interactive_mode) {
            printf("#cisfun$ ");
        }

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
            fprintf(stderr, "./shell: No such file or directory %s\n", command);
            exit(1);
        }
        else {
            /* Parent process */
            int status;
            waitpid(pid, &status, 0);

                  
        }

        if (!interactive_mode) {
            break;  /* Non-interactive mode, exit after executing a single command */
        }
    }

    return 0;
}
