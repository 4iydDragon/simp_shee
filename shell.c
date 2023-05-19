#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "prompt.c"
#include "fork.c"
#include "exec.c"
#include "pid.c"
#include "stat.c"

#define MAX_COMMAND_LENGTH 100

void shell() {
    char command[MAX_COMMAND_LENGTH];
    pid_t pid;
    
    while (1) {
        prompt();

        if (fgets(command, sizeof(command), stdin) == NULL) {
            printf("\n");
            break;
        }

        command[strcspn(command, "\n")] = '\0';

        pid = fork_process();

        if (pid == 0) {
            exec_command(command);
        } else {
            int status;
            waitpid(pid, &status, 0);
            check_status(status, command);
        }
    }
}
