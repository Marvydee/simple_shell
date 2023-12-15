#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARGS 64

// Function to parse user input into commands and arguments
char **parse_input(char *input) {
    // Allocate an array to store commands and arguments
    char **tokens = (char **)malloc((MAX_ARGS + 1) * sizeof(char *));
    if (tokens == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Initialize array elements to NULL
    for (int i = 0; i < MAX_ARGS + 1; i++) {
        tokens[i] = NULL;
    }

    // Tokenize the input string
    const char *delimiters = " \t\n";  // Space, tab, and newline
    char *token = strtok(input, delimiters);
    int i = 0;

    while (token != NULL) {
        // Duplicate and store each token
        tokens[i] = strdup(token);
        if (tokens[i] == NULL) {
            perror("strdup");
            exit(EXIT_FAILURE);
        }

        token = strtok(NULL, delimiters);
        i++;

        // Check if the number of arguments exceeds the maximum limit
        if (i >= MAX_ARGS) {
            fprintf(stderr, "Too many arguments. Maximum allowed: %d\n", MAX_ARGS);
            // Additional error handling can be added here if needed
            exit(EXIT_FAILURE);
        }
    }

    return tokens;
}

