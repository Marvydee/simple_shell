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
			write(STDOUT_FILENO, "\n", 1); /*Handle Ctrl+D (EOF)*/
			break;
		}

		/*Remove the newline character*/
		buffer[strcspn(buffer, "\n")] = '\0';

		execute_command(buffer);
	}

	return (0);
}
