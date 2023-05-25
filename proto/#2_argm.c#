#include <unistd.h>
#include <string.h>
#include <stdlib.h>
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

    if (command[0] != '/')
    {
        return -1;
    }

    return 1;
}

int execute_command(char *command)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        write(STDERR_FILENO, "Failed to fork\n", 15);
        return -1;
    }
    else if (pid == 0)
    {
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

        execve(args[0], args, environ);

        write(STDERR_FILENO, "./shell: No such file or directory\n", 34);

        for (argCount = 0; args[argCount] != NULL; argCount++)
            free(args[argCount]);

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

void handle_error(void)
{
    /* Handle the error here */
}
