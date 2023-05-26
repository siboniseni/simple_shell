#include "shell.h"

/**
 * _strncpy - copies a string
 * @dest: the destination string to be copied to
 * @src: the source string
 * @n: the amount of characters to be copied
 *
 * Return: the pointer to the destination string
 */
char *_strncpy(char *dest, const char *src, int n)
{
	int i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];

	for (; i < n; i++)
		dest[i] = '\0';

	return dest;
}

/**
 * _strncat - concatenates two strings
 * @dest: the first string
 * @src: the second string
 * @n: the maximum number of bytes to be concatenated
 *
 * Return: the pointer to the destination string
 */
char *_strncat(char *dest, const char *src, int n)
{
	int dest_len = 0;
	int i;

	while (dest[dest_len] != '\0')
		dest_len++;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[dest_len + i] = src[i];

	dest[dest_len + i] = '\0';

	return dest;
}

/**
 * _strchr - locates a character in a string
 * @s: the string to be searched
 * @c: the character to be found
 *
 * Return: a pointer to the first occurrence of the character in the string,
 *         or NULL if the character is not found
 */
char *_strchr(const char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return (char *)s;

		s++;
	}

	if (*s == c)
		return (char *)s;

	return NULL;
}
