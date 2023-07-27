#include "shell.h"

int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);
char **_strtok(char *line, char *delim);

/**
 * token_len - Locates the delimiter index showing the end
 * of the first token contained in the string
 * @str: The string to search in
 * @delim: The delimiter character
 *
 * Return: The delimiter index showing the end of
 * the intitial token pointed to the string
 */
int token_len(char *str, char *delim)
{
	int index = 0;
	int length = 0;

	while (*(str + index) && *(str + index) != *delim)
	{
		length++;
		index++;
	}

	return (length);
}

/**
 * count_tokens - Counts the number of delimited
 * words inside the string
 * @str: The string to search in
 * @delim: The delimiter character
 *
 * Return: The number of words inside the string
 */
int count_tokens(char *str, char *delim)
{
	int index;
	int tokens = 0;
	int length = 0;

	for (index = 0; *(str + index); index++)
		length++;

	for (index = 0; index < length  ; index++)
	{
		if (*(str + index) != *delim)
		{
			tokens++;
			index += token_len(str + index, delim);
		}
	}

	return (tokens);
}

/**
 * _strtok - Tokenizes the string
 * @line: The string
 * @delim: The delimiter character
 *
 * Return: A pointer to an array with the tokenized strings
 */
char **_strtok(char *line, char *delim)
{
	char **ptr;
	int index = 0, tokens, a, letters, b;

	tokens = count_tokens(line, delim);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);

	for (a = 0; a < tokens; a++)
	{
		while (line[index] == *delim)
			index++;

		letters = token_len(line + index, delim);

		ptr[a] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[a])
		{
			for (index -= 1; index >= 0; index--)
				free(ptr[index]);
			free(ptr);
			return (NULL);
		}

		for (b = 0; b < letters; b++)
		{
			ptr[a][b] = line[index];
			index++;
		}

		ptr[a][b] = '\0';
	}
	ptr[a] = NULL;
	ptr[a + 1] = NULL;

	return (ptr);
}
