#include <unistd.h>
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

write(STDOUT_FILENO, "\n", 1); /* Add a new line after executing the command */
}

return (0);
}

/**
 * print_prompt - prints the main shell prompt
 */

void print_prompt(void)
{
write(STDOUT_FILENO, "#cisfun$ ", 10);
}

/**
 * read_command - read inputed commands
 * @command: command to be executed
 * Return: returns 0 for success
 */

int read_command(char *command)
{
if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
{
write(STDOUT_FILENO, "\n", 1);
return (0);
}

command[strcspn(command, "\n")] = '\0';

if (command[0] != '/')
{
return (-1);
}

return (1);
}

/**
 * execute_command - does forking for the code
 * Return: returns 0 when succeed and -1 when fail
 * @command: command to be executed
 */

int execute_command(char *command)
{
pid_t pid = fork();

if (pid < 0)
{
write(STDERR_FILENO, "Failed to fork\n", 15);
return (-1);
}
else if (pid == 0)
{
char **args = (char **)malloc(2 * sizeof(char *));
args[0] = strdup(command);
args[1] = NULL;
execve(command, args, environ);

write(STDERR_FILENO, "./shell: No such file or directory\n", 34);
free(args[0]);
free(args);
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
/* Handle the error here */
}
