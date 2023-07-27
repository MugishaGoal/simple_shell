#include "shell.h"

int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);

/**
 * _strlen - Returns the length of the string.
 * @s: A pointer to the characters of the string.
 *
 * Return: The length of the character of the string.
 */
int _strlen(const char *s)
{
	int len = 0;

	if (!s)
		return (len);
	for (len = 0; s[len]; len++)
		;
	return (len);
}

/**
 * _strcpy - Copies the string pointed to by source
 *
 * @dest: Pointer to the destination
 * @src: Pointer to the source
 *
 * Return: Pointer to destination.
 */
char *_strcpy(char *dest, const char *src)
{
	size_t i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcat - Concantenates two strings
 * @dest: Pointer to the destination
 * @src: Pointer to the source
 *
 * Return: Pointer to the destination
 */
char *_strcat(char *dest, const char *src)
{
	char *dest_temp;
	const char *src_temp;

	dest_temp = dest;
	src_temp =  src;

	while (*dest_temp != '\0')
		dest_temp++;

	while (*src_temp != '\0')
		*dest_temp++ = *src_temp++;
	*dest_temp = '\0';
	return (dest);
}

/**
 * _strncat - Concantenates two strings
 * @dest: Pointer to the destination
 * @src: Pointer to the source
 *
 * Return: Pointer to the destination
 */
char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_length = _strlen(dest);
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[dest_length + i] = src[i];
	dest[dest_length + i] = '\0';

	return (dest);
}
