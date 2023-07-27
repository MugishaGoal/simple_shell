#include "shell.h"

void free_args(char **args, char **front);
char *get_pid(void);
char *get_env_value(char *beginning, int len);
void variable_substitution(char **args, int *executed_ret);

/**
 * free_args - Deallocates the memory occupied by the args
 * @args: A null-terminated double pointer containing commands/arguments.
 * @front: A double pointer to the beginning of args.
 */
void free_args(char **args, char **front)
{
	size_t i;

	for (i = 0; args[i] || args[i + 1]; i++)
		free(args[i]);

	free(front);
}

/**
 * get_pid - Retrieves the process ID of the current program
 * Description: This function retrieves the process ID of the current program
 * by reading the "/proc/self/stat" file. It allocates memory for a buffer,
 * opens the file, reads the process information into the buffer,
 * extracts the process ID from the buffer, and returns it as a string.
 * If any error occurs during the process, the function returns NULL.
 *
 * Return: The function returns either the current process ID or
 * NULL if there is a failure.
 */
char *get_pid(void)
{
	size_t i = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Can not read the file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[i] != ' ')
		i++;
	buffer[i] = '\0';

	close(file);
	return (buffer);
}

/**
 * get_env_value - Gets the value corresponding to an environment variable
 * @beginning: The environment variable to find
 * @len: The length of the environment variable to find
 *
 * Return: If the variable is not found an empty string is returned,
 * Otherwise - the value of the environment variable
 *
 * Description: Variables are stored in VARIABLE=VALUE format
 */
char *get_env_value(char *beginning, int len)
{
	char **var_address;
	char *substitution = NULL, *temp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, beginning, len);

	var_address = _getenv(var);
	free(var);
	if (var_address)
	{
		temp = *var_address;
		while (*temp != '=')
			temp++;
		temp++;
		substitution = malloc(_strlen(temp) + 1);
		if (substitution)
			_strcpy(substitution, temp);
	}

	return (substitution);
}

/**
 * variable_substitution - Manages variable substitution
 * @line: A double pointer containing the command and arguments
 * @executed_ret: A pointer to the return value of the last executed command
 *
 * Description:This function performs variable replacement by substituting "$$"
 * with the current process ID, "$?" with the return value of the last executed
 * program, and environmental variables prefixed with "$" with
 * their respective values
 */
void variable_substitution(char **line, int *executed_ret)
{
	int x, y = 0, len;
	char *substitution = NULL;
	char *o_line = NULL;
	char *n_line;

	o_line = *line;
	for (x = 0; o_line[x]; x++)
	{
		if (o_line[x] == '$' && o_line[x + 1] &&
				o_line[x + 1] != ' ')
		{
			if (o_line[x + 1] == '$')
			{
				substitution = get_pid();
				y = x + 2;
			}
			else if (o_line[x + 1] == '?')
			{
				substitution = _itoa(*executed_ret);
				y = x + 2;
			}
			else if (o_line[x + 1])
			{
				for (y = x + 1; o_line[y] &&
						o_line[y] != '$' &&
						o_line[y] != ' '; y++)
					;
				len = y - (x + 1);
				substitution = get_env_value(&o_line[x + 1], len);
			}
			n_line = malloc(x + _strlen(substitution)
					  + _strlen(&o_line[y]) + 1);
			if (!line)
				return;
			n_line[0] = '\0';
			_strncat(n_line, o_line, x);
			if (substitution)
			{
				_strcat(n_line, substitution);
				free(substitution);
				substitution = NULL;
			}
			_strcat(n_line, &o_line[y]);
			free(o_line);
			*line = n_line;
			o_line = n_line;
			x = -1;
		}
	}
}
