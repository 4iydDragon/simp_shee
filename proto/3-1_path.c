#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "shell.h"
#define MAX_COMMAND_LENGTH 100

extern char **environ;

void print_prompt(void);
int read_command(char *command);
int execute_command(char *command);
void handle_error(void);

int main(void)
{
    char command[MAX_COMMAND_LENGTH];
    char **env;
    
    int isTerminal = isatty(STDIN_FILENO);  /* Check if input is coming from a terminal*/

    while (1)
    {
        if (isTerminal) {
            print_prompt();
        }

        if (read_command(command) == 0)
            break;

        if (execute_command(command) != 0)
            handle_error();

        if (isTerminal) {
            write(STDOUT_FILENO, "\n", 1);
        }
    }

    env = environ;
    while (*env != NULL)
    {
        size_t len = strlen(*env);
        write(STDOUT_FILENO, *env, len);
        write(STDOUT_FILENO, "\n", 1);
        env++;
    }

    return 0;
}

void print_prompt(void)
{
    char prompt[] = "#cisfun$ ";
    write(STDOUT_FILENO, prompt, sizeof(prompt) - 1);
}

int read_command(char *command)
{
    size_t bufsize = MAX_COMMAND_LENGTH;
    ssize_t n;

    n = getline(&command, &bufsize, stdin);

    if (n == -1)
    {
        write(STDOUT_FILENO, "\n", 1);
        return 0;
    }

    command[n - 1] = '\0';

    if (strchr(command, '/') == NULL)
    {
      return -1; /* Relative path*/
    }

    return 1; /* Absolute path*/
}

int execute_command(char *command)
{

  char *path_token;
  char *path;
  char *token;
    char *args[MAX_COMMAND_LENGTH];
    int argCount = 0;

    token = strtok(command, " ");
    while (token != NULL)
    {
        args[argCount] = strdup(token);
        argCount++;
        token = strtok(NULL, " ");
    }
    args[argCount] = NULL;

    path = getenv("PATH");
    path_token = strtok(path, ":");

    while (path_token != NULL)
    {
        char command_path[MAX_COMMAND_LENGTH];
        snprintf(command_path, sizeof(command_path), "%s/%s", path_token, args[0]);

        if (access(command_path, X_OK) == 0)
        {
            pid_t pid = fork();

            if (pid < 0)
            {
                write(STDERR_FILENO, "Failed to fork\n", 15);
                return -1;
            }
            else if (pid == 0)
            {
                execvp(command_path, args);
                write(STDERR_FILENO, "./shell: Failed to execute the command\n", 39);
                exit(1);
            }
            else
            {
                int status;
                waitpid(pid, &status, 0);

                if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
                    return -1;
            }
            return 0;
        }

        path_token = strtok(NULL, ":");
    }

    write(STDERR_FILENO, "./shell: Command not found\n", 26);

    for (argCount = 0; args[argCount] != NULL; argCount++)
        free(args[argCount]);

    return -1;
}

void handle_error(void)
{
    /* Handle the error here */
}
