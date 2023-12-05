#include "shell.h"

/**
 * main - entry point
 * Return: always 0
 */
int main(void)
{
	char buffer[BUFFER_SIZE];

	while (1)
	{
		display_prompt();

		if (fgets(buffer, sizeof(buffer), stdin) == NULL)
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}

		buffer[strcspn(buffer, "\n")] = '\0';

		pid_t pid = fork();

		if (pid == -1)
		{
			perror("Fork failed");
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
		{
			if (execlp(buffer, buffer, (char *)NULL) == -1)
			{
				perror("Command not found");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			waitpid(pid, NULL, 0);
		}
	}

	return (0);
}
