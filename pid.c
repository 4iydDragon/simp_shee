#include <stdio.h>
#include <unistd.h>

pid_t get_pid() {
    return getpid();
}

pid_t get_ppid() {
    return getppid();
}
