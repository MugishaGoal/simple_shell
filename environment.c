#include "shell.h"

char **copy_env(void);
void free_env(void);
char **_getenv(const char *var);

/**
 * copy_env - The function creates a copy of an environment
 *
 * Return: If an error occurs - NULL
 * O/w - a double pointer to the new copy
 */
char **copy_env(void)
{
	char **new_env;
	size_t size;
	int index;

	for (size = 0; environ[size]; size++)
		;

	new_env = malloc(sizeof(char *) * (size + 1));
	if (!new_env)
		return (NULL);

	for (index = 0; environ[index]; index++)
	{
		new_env[index] = malloc(_strlen(environ[index]) + 1);

		if (!new_env[index])
		{
			for (index--; index >= 0; index--)
				free(new_env[index]);
			free(new_env);
			return (NULL);
		}
		_strcpy(new_env[index], environ[index]);
	}
	new_env[index] = NULL;

	return (new_env);
}

/**
 * free_env - The function frees an environment copy
 */
void free_env(void)
{
	int index;

	for (index = 0; environ[index]; index++)
		free(environ[index]);
	free(environ);
}

/**
 * _getenv - The function picks the environment variable from the PATH
 * @var: The name of the environment variable to pick
 *
 * Return: If the environment variable does not exist, NULL is returned
 * Otherwise - a pointer to the environment variable
 */
char **_getenv(const char *var)
{
	int index;
	int length;

	length = _strlen(var);
	for (index = 0; environ[index]; index++)
	{
		if (_strncmp(var, environ[index], length) == 0)
			return (&environ[index]);
	}

	return (NULL);
}
