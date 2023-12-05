#include "shell.h"

/**
 * display_prompt - display user prompt
 * Return: no return
 */
void display_prompt(void)
{
	write(STDOUT_FILENO, "#cisfun$ ", 9);
}
