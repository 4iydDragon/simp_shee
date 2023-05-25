#include "ls_shell.h"


/**
 * ls_strlen - returns the length of a string
 * @str: the string to be measured
 *
 * Return: the length of the string
 */
size_t ls_strlen(const char *str)
{
	size_t length = 0;

	while (str[length] != '\0')
	{
		length++;
	}
	return (length);
}

/**
 * main - Entry point
 *
 *
 * Return: 0 on success, otherwise an error code
 */

int main(void)
{
	size_t n = 0;
	char *cmd = NULL;
	pid_t pid;
	int val;
	char *argv[] = {NULL, NULL};

	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);
		if (getline(&cmd, &n, stdin) == -1)
			return (-1);

		if (cmd[ls_strlen(cmd) - 1] == '\n')
			cmd[ls_strlen(cmd) - 1] = '\0';


		pid = fork();
		argv[0] = cmd;

		if (pid == -1)
			return (-1);

		if (pid == 0)
		{
			val = execve(argv[0], argv, NULL);
			if (val == -1)
				perror(argv[0]);
		}
		else
			wait(NULL);

		/***
		 * free(cmd);
		 * */

	}

	return (0);
}
