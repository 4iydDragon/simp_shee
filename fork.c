#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

pid_t fork_process() {
    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Failed to fork\n");
        exit(1);
    }

    return pid;
}
