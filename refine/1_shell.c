#include "shell.h"

/**
 * main - entry point
 * Return: returns o
 */

int main(void)
{
char command[MAX_COMMAND_LENGTH];

while (1)
{
print_prompt();

if (read_command(command) == 0)
break;  /* End of file (Ctrl+D) detected */

if (execute_command(command) != 0)
handle_error();
}

return (0);
}

/**
 *print_prompt - prints the main shell prompt
 */

void print_prompt(void)
{
printf("#cisfun$ ");
}


/**
 *read_command - read inputed commands
 *@command: command to be executed
 *Return: returns 0 for success
 */

int read_command(char *command)
{
if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
{
printf("\n");
return (0);
}

command[strcspn(command, "\n")] = '\0';

if (command[0] != '/')
{
fprintf(stderr, "./shell: No such file or directory\n");
return (-1);
}

return (1);
}

/**
 *execute_command - does forking for the code
 *Return: returns 0 when succed and -1 when fail
 *@command: command to be executed
 */

int execute_command(char *command)
{
pid_t pid = fork();

if (pid < 0)
{
fprintf(stderr, "Failed to fork\n");
return (-1);
}
else if (pid == 0)
{
char *args[] = {command, NULL};
execve(command, args, environ);

fprintf(stderr, "./shell: No such file or directory\n");
exit(1);
}
else
{
int status;
waitpid(pid, &status, 0);

if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
return (-1);
}

return (0);
}


/**
 * handle_error - prints execution error
 */
void handle_error(void)
{
fprintf(stderr, "./shell: Error executing command\n");
}
