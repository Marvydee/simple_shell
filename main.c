#include "shell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 1024
/*
 * main - entry point
 * display_prompt - displays prompts of user
 * Return: 0 always
 */

int main(void) {
	init_shell();

	char input[MAX_INPUT_SIZE];
	int i;

	while (1) {
		display_prompt();

		if (fgets(input, sizeof(input), stdin) == NULL) {
			break; /*EOF*/
		}

		/*Remove newline character from input*/
		input[strcspn(input, "\n")] = '\0';

		if (strlen(input) == 0) {
			continue; /*empty line*/
		}

		/*Check for the exit command to break out of the loop*/
		if (strcmp(input, "exit") == 0) {
			break;
		}

		execute_cmd(input);
	}

	return (0);
}
