#ifndef SHELL_H_
#define SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

void ls_execute(char **argv);
size_t ls_strlen(const char *str);
char** ls_parse_line(char *line);

#endif /* SHELL_H_ */
