#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

pid_t forkProcess() {
    return fork();
}
