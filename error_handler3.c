#include "shell.h"

char *error_126(char **args);
char *error_127(char **args);

/**
 * error_126 - Generates an error message for "permission denied" failures
 * @args: An array of arguments
 *
 * Return: The error message
 */
char *error_126(char **args)
{
	char *error, *h_string;
	int len;

	h_string = _itoa(hist);
	if (!h_string)
		return (NULL);

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
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Permission denied\n");

	free(h_string);
	return (error);
}

/**
 * error_127 - Generates an error message for "command not found" failures
 * @args: An array of arguments
 *
 * Return: The error message
 */
char *error_127(char **args)
{
	char *error, *h_string;
	int len;

	h_string = _itoa(hist);
	if (!h_string)
		return (NULL);

	len = _strlen(name) + _strlen(h_string) + _strlen(args[0]) + 16;
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
	_strcat(error, ": not found\n");

	free(h_string);
	return (error);
}
