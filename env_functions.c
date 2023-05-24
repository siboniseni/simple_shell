#include "shell.h"

/**
 * my_env function - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int my_env(info_t *info)
{
	print_list_str(info->env);
	return (0);
}


/**
 * get_env function - Check if the variable name matches the beginning of the environment variable 
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char* get_env(info_t *info, const char *name)
{
	list_t *node = info->env;

	while (node)
	{
		char *env = node->str;
		size_t i = 0;

		while (env[i] == name[i])
		{
			if (name[i] == '\0')
				return &env[i + 1]; 
			i++;
		}

		node = node->next;
	}

	return NULL; /* Variable not found */
}


/**
 * my_setenv func - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int my_setenv(info_t *info)
{
	if (info->argc != 3) {
		
		_eputs("This number of arguments is not correct!\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * my_unsetenv function - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int my_unsetenv(info_t *info)
{

	if (info->argc == 1) {
		
		_eputs("Few arguements.\n");
		return (1);
	}
	for (int i = 1; i <= info->argc; i++) {
	
		_unsetenv(info, info->argv[i]);
	}
	
	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info) {
	
	list_t *node = NULL;
	
	for (size_t i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	
	return (0);
}
