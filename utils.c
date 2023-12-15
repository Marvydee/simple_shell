#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to free a 2D array of strings
void free_str_array(char **array) {
	for (int i = 0; array[i] != NULL; i++) {
		free(array[i]);
	}
	free(array);
}

// Function to duplicate a 2D array of strings
char **duplicate_str_array(char **array) {
	int size = 0;
	while (array[size] != NULL) {
		size++;
	}

	char **duplicate = (char **)malloc((size + 1) * sizeof(char *));
	if (duplicate == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < size; i++) {
		duplicate[i] = strdup(array[i]);
		if (duplicate[i] == NULL) {
			perror("strdup");
			exit(EXIT_FAILURE);
		}
	}

	duplicate[size] = NULL;
	return duplicate;
}

// Function to trim leading and trailing whitespaces from a string
char *trim_whitespace(char *str) {
	while (isspace((unsigned char)*str)) {
		str++;
	}

	if (*str == 0) {
		return (str);
	}

	char *end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end)) {
		end--;
	}

	*(end + 1) = 0;
	return (str);
}
