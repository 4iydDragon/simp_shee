#include <stdio.h>
#include <unistd.h>
#include "shell.h"

pid_t getCurrentProcessID() {
    return getpid();
}
