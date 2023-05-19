#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

void printEnvironmentVariables() {
    extern char** environ;
    for (char** env = environ; *env != NULL; env++) {
        printf("%s\n", *env);
    }
}
