#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void exit_shell() {
    // Perform any necessary cleanup tasks before exiting
    printf("Exiting shell...\n");
    exit(EXIT_SUCCESS);
}

void env_shell() {
    extern char **environ;  // Access to the environment variables

    // Print each environment variable
    char **env = environ;
    while (*env != NULL) {
        printf("%s\n", *env);
        env++;
    }
}

void cd_shell(char *path) {
    if (path == NULL) {
        // Change to the user's home directory if no path is provided
        char *home_dir = getenv("HOME");
        if (home_dir != NULL) {
            if (chdir(home_dir) != 0) {
                perror("cd");
            }
        } else {
            fprintf(stderr, "cd: HOME not set\n");
        }
    } else {
        // Change to the specified directory
        if (chdir(path) != 0) {
            perror("cd");
        }
    }
}

void execute_cmd(char *input) {
    // Parse the input into commands and arguments
    char **commands = parse_input(input);

    if (commands[0] == NULL) {
        // Empty command, do nothing
        free(commands);
        return;
    }

    // Check for built-in commands
    if (strcmp(commands[0], "exit") == 0) {
        exit_shell();
    } else if (strcmp(commands[0], "env") == 0) {
        env_shell();
    } else if (strcmp(commands[0], "cd") == 0) {
        cd_shell(commands[1]);
    } else {
        // Fork a child process
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            if (execvp(commands[0], commands) == -1) {
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        } else {
            // Parent process
            int status;
            waitpid(pid, &status, 0);

            // Optionally, handle the exit status or other post-execution tasks
            // For example, you can print the exit status:
            // printf("Child process exited with status %d\n", WEXITSTATUS(status));
        }
    }

    // Cleanup
    free(commands);
}

