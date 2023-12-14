#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 256

extern char **environ;  // Ensure environ is declared

int main(void) {
	char buffer[BUFFER_SIZE];
	char *args[BUFFER_SIZE];
	int argc = 0;
	char *path = getenv("PATH");

	while (1) {
		// Display prompt
		printf("($) ");

		// Read user input
		if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
			if (feof(stdin)) {
				printf("\n");
				exit(EXIT_SUCCESS);
			} else {
				perror("fgets error");
				exit(EXIT_FAILURE);
			}
		}

		// Remove newline character
		buffer[strcspn(buffer, "\n")] = '\0';

		// Parse arguments
		char *token = strtok(buffer, " ");
		while (token) {
			args[argc++] = token;
			token = strtok(NULL, " ");
		}
		args[argc] = NULL;

		// Check for built-ins
		if (strcmp(args[0], "exit") == 0) {
			exit(EXIT_SUCCESS);
		} else if (strcmp(args[0], "env") == 0) {
			// Print environment variables
			for (int i = 0; environ[i]; ++i) {
				printf("%s\n", environ[i]);
			}
		} else if (strcmp(args[0], "cd") == 0) {
			// Implement cd functionality (optional)
		} else {
			// Handle non-built-in commands
			int found = 0;
			if (path) {
				char *path_copy = strdup(path);
				char *path_token = strtok(path_copy, ":");
				while (path_token && !found) {
					char full_path[BUFFER_SIZE];
					snprintf(full_path, sizeof(full_path), "%s/%s", path_token, args[0]);
					if (access(full_path, X_OK) == 0) {
						args[0] = full_path;
						found = 1;
					}
					path_token = strtok(NULL, ":");
				}
				free(path_copy);
			}

			if (found) {
				if (execve(args[0], args, environ) == -1) {
					perror("execve error");
				}
			} else {
				printf("%s: command not found\n", args[0]);
			}
		}

		// Reset arguments
		argc = 0;
	}

	return 0;
}

