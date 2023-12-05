#include "shell.h"

/**
 * execute_command - execute a command with arguments.
 * Forks a child process and uses execvp to execute the command.
 * @buffer: input command string
 * Return: no return
 */
void execute_command(char *buffer)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}

	if (pid == 0) /*Child process*/
	{
		char *args[BUFFER_SIZE];

		tokenize_input(buffer, args);

		/*Execute the command with arguments*/
		if (execvp(args[0], args) == -1)
		{
			perror("Command not found");
			exit(EXIT_FAILURE);
		}
	}
	else /*Parent process*/
	{
		waitpid(pid, NULL, 0);
	}
}

