#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void exec_command(char* command) {
    execlp(command, command, (char*) NULL);
    fprintf(stderr, "Command not found: %s\n", command);
    exit(1);
}
