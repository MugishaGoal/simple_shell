#include "shell.h"

char *env_error(char **args);
char *alias_error(char **args);
char *exit_error(char **args);
char *cd_error(char **args);
char *syntax_error(char **args);
/**
 * env_error - Shows an error message for shell_environment
 * @args: An array of arguments
 *
 * Return: The error message
 */
char *env_error(char **args)
{
	char *error, *h_string;
	int len;

	h_string = _itoa(hist);
	if (!h_string)
		return (NULL);

	args--;
	len = _strlen(name) + _strlen(h_string) + _strlen(args[0]) + 45;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(h_string);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, h_string);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Failed to add or remove from the environment\n");

	free(h_string);
	return (error);
}

/**
 * alias_error - Shows an error message for shell_alias
 * @args: An array of arguments
 *
 * Return: The error message
 */
char *alias_error(char **args)
{
	char *error;
	int len;

	len = _strlen(name) + _strlen(args[0]) + 13;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
		return (NULL);

	_strcpy(error, "alias: ");
	_strcat(error, args[0]);
	_strcat(error, " Command not found\n");

	return (error);
}

/**
 * exit_error - Shows an error message for shell_exit
 * @args: An array of arguments
 *
 * Return: The error message
 */
char *exit_error(char **args)
{
	char *error, *h_string;
	int len;

	h_string = _itoa(hist);
	if (!h_string)
		return (NULL);

	len = _strlen(name) + _strlen(h_string) + _strlen(args[0]) + 27;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(h_string);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, h_string);
	_strcat(error, ": exit: Illegal number: ");
	_strcat(error, args[0]);
	_strcat(error, "\n");

	free(h_string);
	return (error);
}

/**
 * cd_error - Shows an error message for shell_change directory
 * @args: An array of arguments
 *
 * Return: The error message
 */
char *cd_error(char **args)
{
	char *error, *h_string;
	int len;

	h_string = _itoa(hist);
	if (!h_string)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
	len = _strlen(name) + _strlen(h_string) + _strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(h_string);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, h_string);
	if (args[0][0] == '-')
		_strcat(error, ": cd: No directory found");
	else
		_strcat(error, ": cd: can not cd to ");
	_strcat(error, args[0]);
	_strcat(error, "\n");

	free(h_string);
	return (error);
}

/**
 * syntax_error - Shows an error message for syntax error
 * @args: An array of arguments
 *
 * Return: The error message
 */
char *syntax_error(char **args)
{
	char *error, *h_string;
	int len;

	h_string = _itoa(hist);
	if (!h_string)
		return (NULL);

	len = _strlen(name) + _strlen(h_string) + _strlen(args[0]) + 33;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(h_string);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, h_string);
	_strcat(error, ": Syntax error!: \"");
	_strcat(error, args[0]);
	_strcat(error, "\" Not correct\n");

	free(h_string);
	return (error);
}
