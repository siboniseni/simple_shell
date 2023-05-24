#include "shell.h"

/**
 * my_exit func - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */

int my_exit(info_t *info)
{
	int exit_check = 0;

	if (info->argv[1]) /* If there is an exit argument */
	{
		char *arg = info->argv[1];
		int i = 0;

		/* Check if the argument is a valid integer */
		while (arg[i] != '\0')
		{
			if (arg[i] < '0' || arg[i] > '9')
			{
				info->status = 2;
				print_error(info, "Invalid number: ");
				_eputs(info->argv[1]);
				_eputchar('\n');
				return 1;
			}
			exit_check = exit_check * 10 + (arg[i] - '0');
			i++;
		}

		info->err_num = exit_check;
		return -2;
	}

	info->err_num = -1;
	return -2;
}


/**
 * my_cd func - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int my_cd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");

	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			dir = _getenv(info, "PWD=") ? _getenv(info, "PWD=") : "/";
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return 1;
		}
		dir = _getenv(info, "OLDPWD=");
	}
	else
	{
		dir = info->argv[1];
	}

	chdir_ret = chdir(dir);

	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]);
		_eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}

	return 0;
}


/**
 * my_help func - the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int my_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

