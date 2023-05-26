#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>


#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

extern char **environ;  /* Declare the 'environ' variable*/

void print_prompt(void);
int read_command(char *command);
int execute_command(char *command);
void handle_error(void);
void exit_shell(void);

bool commandExists(const char *command);

#endif
