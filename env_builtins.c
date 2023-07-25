#include "shell.h"

int shell_env(char **args, char __attribute__((__unused__)) **front);
int shell_setenv(char **args, char __attribute__((__unused__)) **front);
int shell_unsetenv(char **args, char __attribute__((__unused__)) **front);

/**
 * shell_env - Prints the current environment
 * @args: An array of arguments inputed to the shell
 * @front: A double pointer to the starting args
 *
 * Return: If an error occurs - -1
 * Otherwise - 0
 *
 * Description: Prints one variable per line in the
 * format 'variable'='value'
 */
int shell_env(char **args, char __attribute__((__unused__)) **front)
{
	int index;
	char nl = '\n';

	if (!environ)
		return (-1);

	for (index = 0; environ[index]; index++)
	{
		write(STDOUT_FILENO, environ[index], _strlen(environ[index]));
		write(STDOUT_FILENO, &nc, 1);
	}

	(void)args;
	return (0);
}

/**
 * shell_setenv - Changes or creates an environment variable to the PATH
 * @args: An array of arguments inputed to the shell
 * @front: A double pointer to the beginning of args
 * Description: args[1] is the name of the new or existing PATH variable,
 * args[2] is the value to set the new or changed variable to
 *
 * Return: If an error occurs - -1
 * Otherwise - 0
 */
int shell_setenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_variable = NULL, **new_env, *new_value;
	size_t size;
	int index;

	if (!args[0] || !args[1])
		return (create_error(args, -1));

	new_value = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_value)
		return (create_error(args, -1));
	_strcpy(new_value, args[0]);
	_strcat(new_value, "=");
	_strcat(new_value, args[1]);

	env_variable = _getenv(args[0]);
	if (env_variable)
	{
		free(*env_varible);
		*env_variable = new_value;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	new_env = malloc(sizeof(char *) * (size + 2));
	if (!new_env)
	{
		free(new_value);
		return (create_error(args, -1));
	}

	for (index = 0; environ[index]; index++)
		new_env[index] = environ[index];

	free(environ);
	environ = new_env;
	environ[index] = new_value;
	environ[index + 1] = NULL;

	return (0);
}

/**
 * shell_unsetenv - Deletes an environment variable from the PATH
 * @args: An array of arguments passed to the shell
 * @front: A double pointer to the beginning of args
 * Description: args[1] is the PATH variable to remove
 *
 * Return: If an error occurs - -1
 * Otherwise - 0
 */
int shell_unsetenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_variable, **new_env;
	size_t size;
	int index, index2;

	if (!args[0])
		return (create_error(args, -1));
	env_variable = _getenv(args[0]);
	if (!env_variable)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_env = malloc(sizeof(char *) * size);
	if (!new_env)
		return (create_error(args, -1));

	for (index = 0, index2 = 0; environ[index]; index++)
	{
		if (*env_variable == environ[index])
		{
			free(*env_variable);
			continue;
		}
		new_env[index2] = environ[index];
		index2++;
	}
	free(environ);
	environ = new_env;
	environ[size - 1] = NULL;

	return (0);
}
