#include "shell.h"

/**
 * fill_memory - fills memory with a constant byte
 * @buffer: the pointer to the memory area
 * @value: the byte value to fill the buffer with
 * @length: the number of bytes to be filled
 *
 * Return: pointer to the memory area
 */
char *fill_memory(char *buffer, char value, unsigned int length)
{
	unsigned int i;

	for (i = 0; i < length; i++)
		buffer[i] = value;

	return buffer;
}

/**
 * free_string_array - frees an array of strings
 * @strings: the array of strings to free
 */
void free_string_array(char **strings)
{
	char **ptr = strings;

	if (!strings)
		return;

	while (*strings)
		free(*strings++);

	free(ptr);
}

/**
 * reallocate_memory - reallocates a block of memory
 * @ptr: pointer to the previously allocated block
 * @old_size: size of the previous block in bytes
 * @new_size: size of the new block in bytes
 *
 * Return: pointer to the reallocated block
 */
void *reallocate_memory(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!ptr)
		return malloc(new_size);

	if (!new_size)
	{
		free(ptr);
		return NULL;
	}

	if (new_size == old_size)
		return ptr;

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return NULL;

	unsigned int i;
	for (i = 0; i < old_size && i < new_size; i++)
		new_ptr[i] = ((char *)ptr)[i];

	free(ptr);
	return new_ptr;
}
