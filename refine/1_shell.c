#include "shell.h"

int main(void)
{
    char command[MAX_COMMAND_LENGTH];
    pid_t pid;

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

        /* Fork a child process */
        pid = fork();

        if (pid < 0) {
            /* Forking failed */
            fprintf(stderr, "Failed to fork\n");
            continue;
        } else if (pid == 0) {
            /* Child process */
            execlp(command, command, (char*) NULL);

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
