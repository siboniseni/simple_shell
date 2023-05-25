#include "shell.h"

/**
 * get_environment - returns a copy of the environment strings
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: a copy of the environment strings
 */
char **get_environment(info_t *info)
{
	if (info->environment == NULL || info->environment_changed == 1)
	{
		free_string_array(info->environment);
		info->environment = list_to_string_array(info->environment_list);
		info->environment_changed = 0;
	}

	return info->environment;
}

/**
 * unset_environment_variable - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @variable: the string representing the environment variable
 * Return: 1 if the variable was deleted, 0 otherwise
 */
int unset_environment_variable(info_t *info, const char *variable)
{
	list_t *node = info->environment_list;
	size_t index = 0;
	const char *p;

	if (node == NULL || variable == NULL)
		return 0;

	while (node != NULL)
	{
		p = starts_with(node->str, variable);
		if (p != NULL && *p == '=')
		{
			info->environment_changed = delete_node_at_index(&(info->environment_list), index);
			index = 0;
			node = info->environment_list;
			continue;
		}
		node = node->next;
		index++;
	}
	return info->environment_changed;
}

/**
 * set_environment_variable - Initialize a new environment variable
 *                            or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @variable: the string representing the environment variable
 * @value: the string representing the value of the environment variable
 * Return: Always 0
 */
int set_environment_variable(info_t *info, const char *variable, const char *value)
{
	char *buffer = NULL;
	list_t *node;
	const char *p;

	if (variable == NULL || value == NULL)
		return 0;

	buffer = malloc(_strlen(variable) + _strlen(value) + 2);
	if (buffer == NULL)
		return 1;
	_strcpy(buffer, variable);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = info->environment_list;
	while (node != NULL)
	{
		p = starts_with(node->str, variable);
		if (p != NULL && *p == '=')
		{
			free(node->str);
			node->str = buffer;
			info->environment_changed = 1;
			return 0;
		}
		node = node->next;
	}
	add_node_end(&(info->environment_list), buffer, 0);
	free(buffer);
	info->environment_changed = 1;
	return 0;
}
