#include "shell.h"

void exit_shell(void)
{
char **env = environ;

while (*env != NULL)
{
size_t len = strlen(*env);
write(STDOUT_FILENO, *env, len);
write(STDOUT_FILENO, "\n", 1);
env++;
}

exit(0);  /* Exit the shell with a successful status*/
}
