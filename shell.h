#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#define END_OF_FILE -2
#define EXIT -3

/* Global variables for environment, program name,
 * and history count */
extern char **environ;
char *name;
int hist;

/**
 * struct list_s - Introducing a novel structure type
 * that defines a linked list
 * @dir: A directory path
 * @next: A pointer to the other struct list_s
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/**
 * struct builtin_s - Introducing a fresh structure type
 * that defines built-in commands
 * @name: The name of the builtin command
 * @f: A function pointer referencing the function
 * for the built-in command
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;

/**
 * struct alias_s - A fresh struct defining aliases
 * @name: The name of the alias
 * @value: The value of the alias
 * @next: A pointer to the other struct alias_s
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

/* Global aliases for linked list */
alias_t *aliases;

/* For Main runner */
ssize_t _getline(char **lineptr, size_t *n, FILE *channel);
void *_realloc(void *ptr, unsigned int old_sz, unsigned int new_sz);
char **_strtok(char *line, char *delim);
char *get_location(char *command);
list_t *get_path_dir(char *path);
int execute(char **args, char **front);
void free_list(list_t *head);
char *_itoa(int num);

/* For Handling args */
void handle_line(char **line, ssize_t read);
void variable_substitution(char **args, int *executed_ret);
char *get_args(char *line, int *executed_ret);
int invoke_args(char **args, char **front, int *executed_ret);
int execute_args(char **args, char **front, int *executed_ret);
int handle_args(int *executed_ret);
int check_args(char **args);
void free_args(char **args, char **front);
char **replace_aliases(char **args);

/* For String helper */
int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
char *_strcpy(char *dest, const char *src);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

/* Builtins */
int (*get_builtins(char *command))(char **args, char **front);
int shell_exit(char **args, char **front);
int shell_env(char **args, char __attribute__((__unused__)) **front);
int shell_setenv(char **args, char __attribute__((__unused__)) **front);
int shell_unsetenv(char **args, char __attribute__((__unused__)) **front);
int shell_cd(char **args, char __attribute__((__unused__)) **front);
int shell_alias(char **args, char __attribute__((__unused__)) **front);
int shell_help(char **args, char __attribute__((__unused__)) **front);

/*For Environment */
char **copy_env(void);
void free_env(void);
char **_getenv(const char *var);

/* For Errors*/
int create_error(char **args, int er);
char *env_error(char **args);
char *alias_error(char **args);
char *exit_error(char **args);
char *cd_error(char **args);
char *syntax_error(char **args);
char *error_126(char **args);
char *error_127(char **args);

/* For Linked_lists */
alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);

void helper_all(void);
void helper_alias(void);
void helper_cd(void);
void helper_exit(void);
void helper_help(void);
void helper_env(void);
void helper_setenv(void);
void helper_unsetenv(void);
void helper_history(void);

int file_commands(char *file_path, int *executed_ret);
#endif /* _SHELL_H_ */
