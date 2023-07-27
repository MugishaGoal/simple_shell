#include "shell.h"

int num_len(int num);
char *_itoa(int num);
int create_error(char **args, int er);

/**
 * num_len - Calculates the length of digits in a given number
 * @num: The number to calculate
 *
 * Return: The digit length
 */
int num_len(int num)
{
	unsigned int num1;
	int len = 1;

	if (num < 0)
	{
		len++;
		num1 = num * -1;
	}
	else
	{
		num1 = num;
	}
	while (num1 > 9)
	{
		len++;
		num1 /= 10;
	}

	return (len);
}

/**
 * _itoa - Transforms an integer into its corresponding
 * string representation
 * @num: The integer
 *
 * Return: The converted string
 */
char *_itoa(int num)
{
	char *buffer;
	int len = num_len(num);
	unsigned int num_x;

	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);

	buffer[len] = '\0';

	if (num < 0)
	{
		num_x = num * -1;
		buffer[0] = '-';
	}
	else
	{
		num_x = num;
	}

	len--;
	do {
		buffer[len] = (num_x % 10) + '0';
		num_x /= 10;
		len--;
	} while (num_x > 0);

	return (buffer);
}


/**
 * create_error - Outputs error message to the standard error
 * @args: The array of arguments
 * @error: The error value
 *
 * Return: The error value.
 */
int create_error(char **args, int er)
{
	char *error;

	switch (er)
	{
	case -1:
		error = env_error(args);
		break;
	case 1:
		error = alias_error(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			error = exit_error(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = syntax_error(args);
		else
			error = cd_error(args);
		break;
	case 126:
		error = error_126(args);
		break;
	case 127:
		error = error_127(args);
		break;
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
		free(error);
	return (er);

}
