#include "shell.h"

/**
 * str_length - Returns the length of a string.
 * @str: The string whose length to check.
 *
 * Return: The integer length of the string.
 */
int str_length(char *str)
{
    int length = 0;

    if (!str)
        return 0;

    while (str[length] != '\0')
        length++;

    return length;
}

/**
 * str_compare - Performs lexicographic comparison of two strings.
 * @str1: The first string.
 * @str2: The second string.
 *
 * Return: Negative if str1 < str2, positive if str1 > str2, zero if str1 == str2.
 */
int str_compare(char *str1, char *str2)
{
    int i = 0;

    while (str1[i] && str2[i] && str1[i] == str2[i])
        i++;

    if (str1[i] == str2[i])
        return 0;
    else
        return str1[i] < str2[i] ? -1 : 1;
}

/**
 * str_starts_with - Checks if a string starts with a given substring.
 * @str: The string to search.
 * @substr: The substring to find.
 *
 * Return: Address of the next character in str if it starts with substr, or NULL.
 */
char *str_starts_with(const char *str, const char *substr)
{
    while (*substr)
    {
        if (*substr++ != *str++)
            return NULL;
    }

    return (char *)str;
}

/**
 * str_concatenate - Concatenates two strings.
 * @dest: The destination buffer.
 * @src: The source buffer.
 *
 * Return: Pointer to the destination buffer.
 */
char *str_concatenate(char *dest, char *src)
{
    char *result = dest;

    while (*dest)
        dest++;

    while ((*dest++ = *src++))
        ;

    return result;
}

