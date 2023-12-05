#include "shell.h"

/**
 * tokenize_input - Tokenize the input string into arguments.
 * Uses strtok to split the string based on spaces.
 * @buffer: The input string to be tokenized.
 * @args: An array to store the resulting tokens.
 * Return: no return
 */
void tokenize_input(char *buffer, char **args)
{
	char *token = strtok(buffer, " ");
	int i = 0;

	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}

	args[i] = NULL; /*Null-terminate the array*/
}

