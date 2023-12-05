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

		/*Check if the command exists in the PATH*/
		if (access(args[0], X_OK) == 0)
		{
			/*Execute the command with arguments*/
			if (execve(args[0], args, NULL) == -1)
			{
				perror("Execution error");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			/*Command not found in the PATH*/
			write(STDERR_FILENO, "Command not found\n", 18);
			exit(EXIT_FAILURE);
		}
	}
	else /*Parent process*/
	{
		waitpid(pid, NULL, 0);
	}
}

