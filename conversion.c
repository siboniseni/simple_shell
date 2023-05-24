#include "shell.h"

/**
 * erratoi - converts a string to an integer
 * @s: the string to be converted
 * Sign of the number 
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int erratoi(char *s)
{
	int i = 0;
	int sign = 1;  
	int result = 0;

	if (*s == '-')
	{
		sign = -1;
		s++;
	}

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return -1;
		}
		else
			return -1;
	}

	return sign * result;
}


/**
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void printeError(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}


/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int printout_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;

	// Determine the number of digits
	int num_digits = 1;
	unsigned int temp = _abs_;
	while (temp /= 10)
		num_digits++;

	// Calculate the divisor
	int divisor = 1;
	for (int i = 0; i < num_digits - 1; i++)
		divisor *= 10;

	// Print each digit
	for (int i = 0; i < num_digits; i++)
	{
		int digit = current / divisor;
		__putchar('0' + digit);
		count++;
		current %= divisor;
		divisor /= 10;
	}

	return count;
}

/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_numb(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}

	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	if (n == 0)
		*--ptr = '0';

	while (n > 0)
	{
		*--ptr = array[n % base];
		n /= base;
	}

	if (sign)
		*--ptr = sign;

	return ptr;
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void rm_comments(char *buf)
{
	int i = 0;

	while (buf[i] != '\0')
	{
		if (buf[i] == '#' && (i == 0 || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
		i++;
	}
}
