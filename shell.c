#include "shell.h"
#include <unistd.h>
#include <string.h>
/**
 * main - Entry point for the shell program.
 * Return: Always 0.
 */
int main(void)
{
	char buffer[BUFFER_SIZE];
	char *path = "/bin:/usr/bin"; /* Update with your desired PATH */
	size_t len;

	if (setenv("PATH", path, 1) != 0)
	{
		perror("Error setting PATH");
		return (1);
	}
	while (1)
	{
		display_prompt();
		if (fgets(buffer, sizeof(buffer), stdin) == NULL)
		{
			write(STDOUT_FILENO, "\n", 1); /* Handle Ctrl+D (EOF) */
			break;
		}
		len = strlen(buffer);
		if (len > 0 && buffer[len - 1] == '\n')
		{
			buffer[len - 1] = '\0'; /* Remove the newline character */
		}
		if (strcmp(buffer, "env") == 0)
		{
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
