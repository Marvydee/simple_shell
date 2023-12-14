#include "shell.h"

/**
 * main - Entry point for the shell program.
 * Return: Always 0.
 */
int main(void)
{
	char buffer[BUFFER_SIZE];

	/* Set up the PATH environment variable */
	char *path = "/bin:/usr/bin";	/* Update with your desired PATH */

	setenv("PATH", path, 1);

	while (1)
	{
		display_prompt();

		if (fgets(buffer, sizeof(buffer), stdin) == NULL)
		{
			write(STDOUT_FILENO, "\n", 1);	/* Handle Ctrl+D (EOF) */
			break;
		}

		/* Remove the newline character */
		buffer[strcspn(buffer, "\n")] = '\0';

		if (strcmp(buffer, "env") == 0)
		{
			/* Handle the env built-in */
			char **env = environ;

			while (*env != NULL)
			{
				write(STDOUT_FILENO, *env, strlen(*env));
				write(STDOUT_FILENO, "\n", 1);
				env++;
			}
		else if ((strcmp(buffer, "exit") == 0)
				exit(0);
		}
		else
		{
			execute_command(buffer);
		}
	}

	return (0);
}
