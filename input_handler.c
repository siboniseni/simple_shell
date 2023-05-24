#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_bufr(info_t *info, char **buffer, size_t *length)
{
	ssize_t bytesRead = 0;
	size_t newLength = 0;

	if (*length == 0)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);

		/* Read input from user */
		char *input = NULL;
		size_t inputSize = 0;
		bytesRead = getline(&input, &inputSize, stdin);

		if (bytesRead > 0)
		{
			/* Remove trailing newline */
			if (input[bytesRead - 1] == '\n')
			{
				input[bytesRead - 1] = '\0';
				bytesRead--;
			}

			info->linecount_flag = 1;
			remove_comments(input);
			build_history_list(info, input, info->histcount++);

			/* Check if it's a command chain */
			char *semicolonPtr = strchr(input, ';');
			if (semicolonPtr)
			{
				newLength = bytesRead;
				*buffer = input;
			}
			else
			{
				free(input);
			}
		}
		else
		{
			free(input);
		}
	}

	*length = newLength;
	return bytesRead;
}
/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_inp(info_t *info)
{
	static char *commandChainBuffer;
	static size_t currentPosition, lastPosition, bufferLength;
	ssize_t bytesRead = 0;
	char **commandPtr = &(info->arg);
	char *currentCommand;

	_putchar(BUF_FLUSH);
	bytesRead = input_buf(info, &commandChainBuffer, &bufferLength);
	if (bytesRead == -1)
		return -1;

	if (bufferLength)
	{
		lastPosition = currentPosition;
		currentCommand = commandChainBuffer + currentPosition;

		check_chain(info, commandChainBuffer, &lastPosition, currentPosition, bufferLength);

		while (lastPosition < bufferLength)
		{
			if (is_chain(info, commandChainBuffer, &lastPosition))
				break;
			lastPosition++;
		}

		currentPosition = lastPosition + 1;

		if (currentPosition >= bufferLength)
		{
			currentPosition = bufferLength = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*commandPtr = currentCommand;
		return strlen(currentCommand);
	}

	*commandPtr = commandChainBuffer;
	return bytesRead;
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_bufr(info_t *info, char *buffer, size_t *index)
{
	ssize_t bytesRead = 0;

	if (*index)
		return 0;

	bytesRead = read(info->readfd, buffer, READ_BUF_SIZE);
	if (bytesRead >= 0)
		*index = bytesRead;

	return bytesRead;
}


/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t bufferIndex, bufferSize;
	size_t bytesRead, newLength;
	ssize_t readResult;
	char *newPtr, *currentPtr;

	currentPtr = *ptr;
	if (currentPtr && length)
		newLength = *length;
	if (bufferIndex == bufferSize)
	{
		bufferIndex = bufferSize = 0;
	}

	readResult = read_buf(info, buffer, &bufferSize);
	if (readResult == -1 || (readResult == 0 && bufferSize == 0))
		return -1;

	char *newlinePtr = strchr(buffer + bufferIndex, '\n');
	bytesRead = newlinePtr ? 1 + (unsigned int)(newlinePtr - buffer) : bufferSize;

	newPtr = realloc(currentPtr, newLength ? newLength + bytesRead : bytesRead + 1);
	if (!newPtr)
	{
		if (currentPtr)
			free(currentPtr);
		return -1;
	}

	if (newLength)
		strncat(newPtr, buffer + bufferIndex, bytesRead - bufferIndex);
	else
		strncpy(newPtr, buffer + bufferIndex, bytesRead - bufferIndex + 1);

	newLength += bytesRead - bufferIndex;
	bufferIndex = bytesRead;
	*ptr = newPtr;
	if (length)
		*length = newLength;

	return newLength;
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sgntHandler(int signalNumber)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
	(void)signalNumber; // Unused parameter
}
