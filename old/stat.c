#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

void check_status(int status, char* command) {
    if (WIFEXITED(status) && WEXITSTATUS(status) == 1) {
        fprintf(stderr, "Command execution failed: %s\n", command);
    }
}
