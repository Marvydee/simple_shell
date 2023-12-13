#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

#define BUFFER_SIZE 1024

void display_prompt(void);
void execute_command(char *command);
void tokenize_input(char *input, char *args[]);
int find_executable(char *command);
int main(void);

#endif
