#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HISTORY_SIZE 100

// Static array to store command history
static char *history[MAX_HISTORY_SIZE];
static int history_count = 0;

// Function to add a command to the history
void add_to_history(char *command) {
    // Check if history is full, shift elements if necessary
    if (history_count == MAX_HISTORY_SIZE) {
        free(history[0]);  // Free the oldest command
        for (int i = 0; i < MAX_HISTORY_SIZE - 1; i++) {
            history[i] = history[i + 1];  // Shift elements
        }
        history_count--;
    }

    // Duplicate and store the command
    history[history_count] = strdup(command);
    if (history[history_count] == NULL) {
        perror("strdup");
        exit(EXIT_FAILURE);
    }

    history_count++;
}

// Function to display command history
void display_history() {
    printf("Command History:\n");
    for (int i = 0; i < history_count; i++) {
        printf("%d. %s\n", i + 1, history[i]);
    }
}
