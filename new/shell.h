#ifndef SHELL_H
#define SHELL_H

#include <sys/types.h>

void executeCommand(char* command);
pid_t forkProcess();
pid_t getCurrentProcessID();
pid_t getParentProcessID();
void displayPrompt();
void waitForChildProcess(pid_t pid, char* command);
void printProcessStats(pid_t pid);
void waitForProcess(pid_t pid, int* status);
void printEnvironmentVariables();

#endif  /* SHELL_H */
