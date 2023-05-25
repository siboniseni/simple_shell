#include "shell.h"

/**
 * count_list_nodes - counts the number of nodes in a linked list
 * @head: pointer to the head of the list
 *
 * Return: number of nodes in the list
 */
size_t count_list_nodes(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		head = head->next;
		count++;
	}

	return count;
}

/**
 * convert_list_to_strings - converts a linked list to an array of strings
 * @head: pointer to the head of the list
 *
 * Return: array of strings
 */
char **convert_list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t count = count_list_nodes(head);
	char **strings;
	char *str;

	if (!head || !count)
		return NULL;

	strings = malloc(sizeof(char *) * (count + 1));
	if (!strings)
		return NULL;

	for (size_t i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (size_t j = 0; j < i; j++)
				free(strings[j]);
			free(strings);
			return NULL;
		}

		str = _strcpy(str, node->str);
		strings[i] = str;
	}

	strings[count] = NULL;
	return strings;
}

/**
 * print_linked_list - prints all elements of a linked list
 * @head: pointer to the head of the list
 *
 * Return: number of nodes in the list
 */
size_t print_linked_list(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		_puts(convert_number(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		count++;
	}

	return count;
}

/**
 * find_node_starts_with - finds a node whose string starts with a prefix
 * @head: pointer to the head of the list
 * @prefix: string to match as prefix
 * @c: the character to match after the prefix
 *
 * Return: matching node or NULL if not found
 */
list_t *find_node_starts_with(list_t *head, char *prefix, char c)
{
	char *p = NULL;

	while (head)
	{
		p = starts_with(head->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return head;
		head = head->next;
	}

	return NULL;
}

/**
 * get_node_index - gets the index of a node in a linked list
 * @head: pointer to the head of the list
 * @node: pointer to the node
 *
 * Return: index of the node or -1 if not found
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return index;
		head = head->next;
		index++;
	}

	return -1;
}
