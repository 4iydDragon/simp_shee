#include "shell.h"

bool commandExists(const char* command) {
    char* path = getenv("PATH");
    char* dir = strtok(path, ":");

    while (dir != NULL) {
        char commandPath[MAX_COMMAND_LENGTH];
        snprintf(commandPath, sizeof(commandPath), "%s/%s", dir, command);

        if (access(commandPath, F_OK | X_OK) == 0) {
            return true;
        }

        dir = strtok(NULL, ":");
    }

    return false;
}

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

        /* Tokenize the command line */
        num_arguments = 0;  /* Reset num_arguments to 0 for each new command*/
        arguments[num_arguments] = strtok(command, " ");

        while (arguments[num_arguments] != NULL && num_arguments < MAX_ARGUMENTS - 1) {
            num_arguments++;
            arguments[num_arguments] = strtok(NULL, " ");
        }

        arguments[num_arguments] = NULL; /* Set the last element to NULL for exec functions*/

        /* Check if the command exists */
        if (!commandExists(arguments[0])) {
            fprintf(stderr, "./shell: Command not found: %s\n", arguments[0]);
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
            execvp(arguments[0], arguments);

            /* If the above line is executed, it means the executable was not found */
            fprintf(stderr, "./shell: Failed to execute command: %s\n", arguments[0]);
            exit(1);
        } else {
            /* Parent process */
            int status;
            waitpid(pid, &status, 0);

            if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                fprintf(stderr, "./shell: Error executing command: %s\n", arguments[0]);
            }
        }
    }

    return 0;
}
