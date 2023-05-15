#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

/**
 ** main - Entry point of the program
 *
 * Return: 0
 * This code works as follows:
 *
 * The program first prints a prompt, "#cisfun$ ".
 * The program then reads a line of input from the user.
 * The program parses the input into a command and its arguments.
 * The program executes the command using the execvp() function.
 * If the command fails, the program prints an error message and 
 * displays the prompt again.
 */

int main() {
  char input[1024];
  char *command;
  char *args[10];
  int i;

  while (1) {
    printf("#cisfun$ ");
    fgets(input, 1024, stdin);
    input[strlen(input) - 1] = '\0';

    command = strtok(input, " ");
    for (i = 0; command != NULL; i++) {
      args[i] = command;
      command = strtok(NULL, " ");
    }

    if (strcmp(command, "exit") == 0) {
      break;
    } else if (feof(stdin)) {
      printf("End of file\n");
      break;
    }

    int status = execvp(args[0], args);
    if (status != 0) {
      printf("Error: %d\n", status);
    }
  }

  return 0;
}
