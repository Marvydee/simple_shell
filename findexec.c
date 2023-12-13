#include "shell.h"

/**
 * find_executable - Finds the full path of the executable command.
 * @command: The command to find.
 * Return: 1 if executable found, 0 otherwise.
 */
int find_executable(char *command)
{
	char *path;
	char *token;

	if (command == NULL)
	{
		fprintf(stderr, "Invalid command\n");
		exit(EXIT_FAILURE);
	}
	path = getenv("PATH");

	if (path == NULL)
	{
		fprintf(stderr, "PATH environment variable is not set\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(path, ":");

	while (token != NULL)
	{
		char *executable_path = malloc(strlen(token) + strlen(command) + 2);

		if (executable_path == NULL)
		{
			perror("Memory allocation error");
			exit(EXIT_FAILURE);
		}
		sprintf(executable_path, "%s/%s", token, command);

		if (access(executable_path, X_OK) == 0)
		{
			free(executable_path);
			return (1); /* Executable found in PATH directory */
		}

		free(executable_path);
		token = strtok(NULL, ":");
	}
	return (0);
}

