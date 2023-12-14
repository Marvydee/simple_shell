#ifndef SHELL_H
#define SHELL_H

#define MAX_VARIABLES 100

/*main.c*/
void init_shell(void);
void display_prompt(void);
char *read_user_input(void);
void execute_cmd(char *input);

/*builtins.c*/
void exit_shell(void);
void env_shell(void);
void cd_shell(char *directory);
void setenv_shell(char *name, char *value);
void unsetenv_shell(char *name);
void alias_shell(char *alias, char *command);
void unset_shell(char *alias);
void echo_shell(char **args);
void history_shell(void);

/*parser.c*/
char **parse_input(char *input);

/*executor.c*/
void execute_command(char **args);
void execute_commands(char ***commands, char **operators, int num_commands);
int execute_builtin(char **args);

/*history.c*/
void add_to_history(char *command);
void display_history(void);

/*variables.c*/
void set_variable(char *variable);
void unset_variable(char *variable);
char *replace_variables(char *command);

/*utils.c*/
void free_str_array(char **array);
char **duplicate_str_array(char **array);
char *trim_whitespace(char *str);

#endif
