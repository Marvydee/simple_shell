#include "shell.h"

/**
 * tokenize_input - Tokenizes the input string into an array of arguments.
 * @input: The input string to tokenize.
 * @args: An array to store the tokenized arguments.
 * Return: No return value.
 */
void tokenize_input(char *input, char *args[])
{
	int i = 0;
	char *token = strtok(input, "	");

	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, "	");
	}

	args[i] = NULL; /* Null-terminate the arguments array */
}
