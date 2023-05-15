#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

/**
 * main - Entry point of the program
 * Return: 0
 * This code works as follows:
 *
 * The program first prints a prompt, "#cisfun$ ".
 * The program then reads a line of input from the user.
 * The program parses the input into a command and its arguments.
 * The program checks if the command exists in the PATH.
 * If the command exists, the program executes the command.
 * If the command does not exist, the program prints an error message.
 * If the user presses Ctrl+D, the program prints a message and exits.
 * If the user types the command exit, the program exits without
 * executing any command
 */

int main(void)
{
char input[1024], char *command, char *args[10], int i, char *path, int status;

while (1)
{printf("#cisfun$ ");
fgets(input, 1024, stdin);
input[strlen(input) - 1] = '\0';

command = strtok(input, " ");
for (i = 0; command != NULL; i++)
{ args[i] = command;
command = strtok(NULL, " "); }

if (strcmp(command, "exit") == 0)
{break; }
else if (feof(stdin))
{ printf("End of file\n");
break; }

path = getenv("PATH");
if (path == NULL)
{printf("Error: PATH not set\n");
continue; }

for (i = 0; path[i] != '\0'; i++)
{char *bin = strtok(&path[i], ":");
if (bin == NULL)
{continue; }

status = execve(bin, args, environ);
if (status == 0)
{break; } }

if (status != 0)
{printf("Error: %d\n", status); } }

if (strcmp(command, "exit") == 0)
{printf("Goodbye!\n");
return (0); }

return (0); }
