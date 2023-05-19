#include <stdio.h>
#include "shell.h"
#include <unistd.h>


void executeCommand(char* command) {
    execlp(command, command, (char*) NULL);
    fprintf(stderr, "Command not found: %s\n", command);
}
