#include "shell.h"
/**
 *main - Entry point for the simple shell.
 *Return: Always 0.
 */
int main(void);

int main(void)
{
	char *buffer;
	size_t bufsize;
	char *args[2];
	pid_t pid;

	bufsize = BUFFER_SIZE;
	buffer = (char *)malloc(bufsize * sizeof(char));
	if (buffer == NULL)
	{
		perror("Unable to allocate buffer");
		exit(1);
	}
	while (1)
	{
		int status;

		printf("%s", PROMPT);
		if (getline(&buffer, &bufsize, stdin) == -1)
		{
			printf("\n");
			break;
		}
		buffer[strcspn(buffer, "\n")] = '\0';
		pid = fork();
		if (pid == -1)
		{
			perror("Fork failed");
			exit(1);
		}
		if (pid == 0)
		{
			args[0] = buffer;
			args[1] = NULL;
			if (execve(buffer, args, NULL) == -1)
			{
				perror("Command not found");
				exit(1);
			}
		} else
		{
			waitpid(pid, &status, 0);
		}
	}
	free(buffer);
	return (0);
}
