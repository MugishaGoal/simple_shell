#include "shell.h"

void *_realloc(void *ptr, unsigned int old_sz, unsigned int new_sz);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t _getline(char **lineptr, size_t *n, FILE *channel);

/**
 * _realloc - Reallocates a memory block using malloc and free
 * @ptr: A pointer to the allocated memory before
 * @old_sz: The size in bytes of the allocated space for pointer
 * @new_sz: The size in bytes for the new memory block
 *
 * Return: If new_sz == old_sz - ptr
 *         If new_sz == 0 and ptr is not NULL - NULL
 *         Otherwise - a pointer to the reallocated memory block
 */
void *_realloc(void *ptr, unsigned int old_sz, unsigned int new_sz)
{ 
	void *mem;
	char *pointer_cpy, *padding;
	unsigned int index;

	if (new_sz == old_sz)
		return (ptr);

	if (ptr == NULL)
	{
		mem = malloc(new_sz);
		if (mem == NULL)
			return (NULL);

		return (mem);
	}

	if (new_sz == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	pointer_cpy = ptr;
	mem = malloc(sizeof(*pointer_cpy) * new_sz);
	if (mem == NULL)
	{
		free(ptr);
		return (NULL);
	}

	padding = mem;

	for (index = 0; index < old_sz && index < new_sz; index++)
		padding[index] = *pointer_cpy++;

	free(ptr);
	return (mem);
}

/**
 * assign_lineptr - Reassigns the line pointer variable for _getline
 * @lineptr: A buffer to store an input string
 * @n: The size of line pointer
 * @buffer: The string to assign to line pointer
 * @b: The size of the buffer
 */
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t x)
{
	if (*lineptr == NULL)
	{
		if (x > 120)
			*n = x;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else if (*n < x)
	{
		if (x > 120)
			*n = x;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * _getline - Reads input from a channel
 * @lineptr: A buffer to store the input
 * @n: The size of lineptr
 * @channel: The channel to read from
 *
 * Return: The number of bytes read
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *channel)
{
	static ssize_t input;
	ssize_t ret;
	char c = 'y', *buffer;
	int a;

	if (input == 0)
		fflush(channel);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * 120);
	if (!buffer)
		return (-1);

	while (c != '\n')
	{
		r = read(STDIN_FILENO, &c, 1);
		if (r == -1 || (a == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (a == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= 120)
			buffer = _realloc(buffer, input, input + 1);

		buffer[input] = c;
		input++;
	}
	buffer[input] = '\0';

	assign_lineptr(lineptr, n, buffer, input);

	ret = input;
	if (a != 0)
		input = 0;
	return (ret);
}
