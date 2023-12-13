#include "shell.h"
/**
 * execute_command - Executes the specified command.
 * @command: The command to execute.
 * Return: No return value.
 */
void execute_command(char *command)
{
	pid_t pid = fork();
	char *args[2];

	if (pid == -1)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	args[0] = command;
	args[1] = NULL;

	if (pid == 0)
	{
		if (execve(command, args, NULL) == -1)
		{
			perror("Execution error");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		int st;

		if (waitpid(pid, &st, 0) == -1)
		{
			perror("Waitpid failed");
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(st))
		{
			int ex_st = WEXITSTATUS(st);

			if (ex_st != 0)
				fprintf(stderr, "Command '%s' exited with status %d\n", command, ex_st);
		}
		else if (WIFSIGNALED(st))
			fprintf(stderr, "Command '%s' kill by signal %d\n", command, WTERMSIG(st));
	}
}
