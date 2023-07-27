#include "shell.h"

int can_not_open(char *file_path);
int file_commands(char *file_path, int *executed_ret);

/**
 * can_not_open - If the file doesn't exist or doesn't have full permissions, print
 * the can not open error
 * @file_path: Path to the corresponding file
 *
 * Return: 127.
 */

int can_not_open(char *file_path)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (127);

	len = _strlen(name) + _strlen(hist_str) + _strlen(file_path) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (127);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": Can not open ");
	_strcat(error, file_path);
	_strcat(error, "\n");

	free(hist_str);
	write(STDERR_FILENO, error, len);
	free(error);
	return (127);
}

/**
 * file_commands - Receives a file and starts to run the commands stored
 * inside it
 * @file_path: Path to the file
 * @executed_ret: Return value of the last executed command
 *
 * Return: If file couldn't be opened - 127
 * If malloc fails - -1
 * Otherwise return the value of the last command executed
 */
int file_commands(char *file_path, int *executed_ret)
{
	ssize_t file, b_reading, i;
	unsigned int line_size = 0;
	unsigned int old_size = 120;
	char *line, **args, **front;
	char buffer[120];
	int ret;

	hist = 0;
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*executed_ret = can_not_open(file_path);
		return (*executed_ret);
	}
	line = malloc(sizeof(char) * old_size);
	if (!line)
		return (-1);
	do {
		b_reading = read(file, buffer, 119);
		if (b_reading == 0 && line_size == 0)
			return (*executed_ret);
		buffer[b_reading] = '\0';
		line_size += b_reading;
		line = _realloc(line, old_size, line_size);
		_strcat(line, buffer);
		old_size = line_size;
	} while (b_reading);
	for (i = 0; line[i] == '\n'; i++)
		line[i] = ' ';
	for (; i < line_size; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = ';';
			for (i += 1; i < line_size && line[i] == '\n'; i++)
				line[i] = ' ';
		}
	}
	variable_substitution(&line, executed_ret);
	handle_line(&line, line_size);
	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (0);
	if (check_args(args) != 0)
	{
		*executed_ret = 2;
		free_args(args, args);
		return (*executed_ret);
	}
	front = args;

	for (i = 0; args[i]; i++)
	{
		if (_strncmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			ret = invoke_args(args, front, executed_ret);
			args = &args[++i];
			i = 0;
		}
	}

	ret = invoke_args(args, front, executed_ret);

	free(front);
	return (ret);
}
