#include "shell.h"

void helper_env(void);
void helper_setenv(void);
void helper_unsetenv(void);
void helper_history(void);

/**
 * helper_env - Shows information about the shell "env" builtin command
 */
void helper_env(void)
{
	char *msg = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * helper_setenv - Shows information about the shell "setenv" builtin command
 */
void helper_setenv(void)
{
	char *msg = "setenv: setenv [VARIABLE] [VALUE]\n\tCreates a new";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "\tWhen it fails, it prints a message to the stderr.\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * helper_unsetenv - Shows information about the shell  "unsetenv" builtin command
 *
 */
void helper_unsetenv(void)
{
	char *msg = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "environmental variable.\n\n\tWhen it fails, it prints a ";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "message to stderr.\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
}
