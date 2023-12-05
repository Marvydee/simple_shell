#include "shell.h"
/**
 * main - entry point
 * Return: always 0
 */
int main(void)
{
	char buffer[BUFFER_SIZE];
	pid_t pid;

	while (1)
	{
		display_prompt();

		if (fgets(buffer, sizeof(buffer), stdin) == NULL)
		{
			write(STDOUT_FILENO, "\n", 1); /*Handle Ctrl+D (EOF)*/
			break;
		}

		/*Remove the newline character*/
		buffer[strcspn(buffer, "\n")] = '\0';

		pid = fork();

		if (pid == -1)
		{
			perror("Fork failed");
			exit(EXIT_FAILURE);
		}

		if (pid == 0) /*Child process*/
		{
			if (execlp(buffer, buffer, (char *)NULL) == -1)
			{
				perror("Command not found");
				exit(EXIT_FAILURE);
			}
		}
		else /*parent process*/
		{
			waitpid(pid, NULL, 0);
		}
	}

	return (0);
}
