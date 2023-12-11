#include "shell.h"

/**
 * execute_command - Executes the specified command.
 * @command: The command to execute.
 * Return: No return value.
 */
void execute_command(char *command)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		/* Implementation of child process */
		if (execve(command, args, NULL) == -1)
		{
			perror("Execution error");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
}
