#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

void waitForChildProcess(pid_t pid, char* command) {
    int status;
    waitpid(pid, &status, 0);

    if (WIFEXITED(status) && WEXITSTATUS(status) == 1) {
        fprintf(stderr, "Command execution failed: %s\n", command);
    }
}
