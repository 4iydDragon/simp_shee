#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include "shell.h"

void waitForProcess(pid_t pid, int* status) {
    waitpid(pid, status, 0);
}
