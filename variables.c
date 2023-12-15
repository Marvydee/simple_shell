#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VARIABLES 100

// Static array to store environment variables
static char *variables[MAX_VARIABLES];
static int variables_count = 0;

// Function to set a variable
void set_variable(char *variable) {
	// Duplicate and store the variable
	variables[variables_count] = strdup(variable);
	if (variables[variables_count] == NULL) {
		perror("strdup");
		exit(EXIT_FAILURE);
	}

	variables_count++;
}

// Function to unset a variable
void unset_variable(char *variable) {
	// Search for the variable and remove it
	for (int i = 0; i < variables_count; i++) {
		if (strcmp(variables[i], variable) == 0) {
			free(variables[i]);  // Free the memory allocated for the variable
			// Shift elements to remove the unset variable
			for (int j = i; j < variables_count - 1; j++) {
				variables[j] = variables[j + 1];
			}
			variables_count--;
			break;  // Exit the loop once the variable is found and unset
		}
	}
}

// Function to replace variables in a command string
char *replace_variables(char *command) {
	char *result = strdup(command);
	if (result == NULL) {
		perror("strdup");
		exit(EXIT_FAILURE);
	}

	// Replace variables in the command string
	for (int i = 0; i < variables_count; i++) {
		char *variable = variables[i];
		char *replace_str = getenv(variable);

		if (replace_str != NULL) {
			// Perform the variable replacement in the result string
			char *pos = strstr(result, variable);
			while (pos != NULL) {
				// Calculate the position and length of the variable in the command
				size_t position = pos - result;
				size_t length = strlen(variable);

				// Allocate memory for the new string
				char *new_result = (char *)malloc(position + strlen(replace_str) + strlen(pos + length) + 1);
				if (new_result == NULL) {
					perror("malloc");
					exit(EXIT_FAILURE);
				}

				// Copy the content before the variable
				strncpy(new_result, result, position);
				new_result[position] = '\0';

				// Concatenate the replacement string
				strcat(new_result, replace_str);

				// Concatenate the content after the variable
				strcat(new_result, pos + length);

				// Free the previous result and update it
				free(result);
				result = new_result;

				// Search for the next occurrence of the variable
				pos = strstr(result, variable);
			}
		}
	}

	return result;
}

