#include "shell.h"

char *get_args(char *line, int *executed_ret);
int invoke_args(char **args, char **front, int *executed_ret);
int execute_args(char **args, char **front, int *executed_ret);
int handle_args(int *executed_ret);
int check_args(char **args);

/**
 * get_args - Retrieves a command from the standard input
 * @line: A buffer to store the command.
 * @executed_ret: The return value of the last executed command.
 *
 * Return: If an error occurs NULL is returned,
 * Otherwise - a pointer to the stored command
 */
char *get_args(char *line, int *executed_ret)
{
	size_t n = 0;
	ssize_t read;
	char *prompt = "incredibleshell# ";

	if (line)
		free(line);

	read = _getline(&line, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_args(line, executed_ret));
	}

	line[read - 1] = '\0';
	variable_substitution(&line, executed_ret);
	handle_line(&line, read);

	return (line);
}

/**
 * invoke_args - Splits operators from commands and invokes them accordingly
 * @args: An array of arguments
 * @front: A double pointer
 * @executed_ret: The return value of the last executed command.
 *
 * Return: The value of the last executed command.
 */
int invoke_args(char **args, char **front, int *executed_ret)
{
	int ret, index;

	if (!args[0])
		return (*executed_ret);
	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], "||", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = replace_aliases(args);
			ret = execute_args(args, front, executed_ret);
			if (*executed_ret != 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (ret);
			}
		}
		else if (_strncmp(args[index], "&&", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = replace_aliases(args);
			ret = execute_args(args, front, executed_ret);
			if (*executed_ret == 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (ret);
			}
		}
	}
	args = replace_aliases(args);
	ret = execute_args(args, front, executed_ret);
	return (ret);
}

/**
 * execute_args - Initiates the execution of a command
 * @args: An array of arguments.
 * @front: A double pointer
 * @executed_ret: The return value of the last executed command
 *
 * Return: The return value of the last executed command.
 */
int execute_args(char **args, char **front, int *executed_ret)
{
	int ret, i;
	int (*builtin)(char **args, char **front);

	builtin = get_builtins(args[0]);

	if (builtin)
	{
		ret = builtin(args + 1, front);
		if (ret != EXIT)
			*executed_ret = ret;
	}
	else
	{
		*executed_ret = execute(args, front);
		ret = *executed_ret;
	}

	hist++;

	for (i = 0; args[i]; i++)
		free(args[i]);

	return (ret);
}

/**
 * handle_args - Retrieves, invokes, and executes a command
 * @executed_ret: The return value of the last executed command
 *
 * Return: If an end-of-file is read - END_OF_FILE (-2)
 * If the input cannot be tokenized - -1.
 * O/w - The exit value of the last executed command
 */
int handle_args(int *executed_ret)
{
	int ret = 0, index;
	char **args, *line = NULL, **front;

	line = get_args(line, executed_ret);
	if (!line)
		return (END_OF_FILE);

	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (ret);
	if (check_args(args) != 0)
	{
		*executed_ret = 2;
		free_args(args, args);
		return (*executed_ret);
	}
	front = args;

	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], ";", 1) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			ret = invoke_args(args, front, executed_ret);
			args = &args[++index];
			index = 0;
		}
	}
	if (args)
		ret = invoke_args(args, front, executed_ret);

	free(front);
	return (ret);
}
/**
 * check_args - Determines the presence of leading ';', ';;', '&&', or '||'
 * in the input
 * @args: A double pointer to tokenized inputs
 *
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2
 * Otherwise - 0.
 */
int check_args(char **args)
{
	size_t i;
	char *cur, *nex;

	for (i = 0; args[i]; i++)
	{
		cur = args[i];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (i == 0 || cur[1] == ';')
				return (create_error(&args[i], 2));
			nex = args[i + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (create_error(&args[i + 1], 2));
		}
	}
	return (0);
}
