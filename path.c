#include "shell.h"

/**
 * isExecutable - Checks if a file is an executable command.
 * @info: The info struct.
 * @filePath: Path to the file.
 *
 * Return: 1 if the file is executable, 0 otherwise.
 */
int isExecutable(info_t *info, char *filePath)
{
    struct stat fileStat;

    (void)info;
    if (!filePath || stat(filePath, &fileStat))
        return 0;

    if (fileStat.st_mode & S_IFREG)
    {
        return 1;
    }
    return 0;
}

/**
 * copyCharacters - Creates a new buffer by duplicating characters.
 * @source: The source string.
 * @start: Starting index.
 * @stop: Stopping index.
 *
 * Return: Pointer to the new buffer.
 */
char *copyCharacters(char *source, int start, int stop)
{
    static char buffer[1024];
    int k = 0;

    for (int i = start; i < stop; i++)
    {
        if (source[i] != ':')
        {
            buffer[k++] = source[i];
        }
    }
    buffer[k] = '\0';
    return buffer;
}

/**
 * findExecutablePath - Finds the full path of a command in the PATH string.
 * @info: The info struct.
 * @pathString: The PATH string.
 * @command: The command to find.
 *
 * Return: The full path of the command if found, or NULL.
 */
char *findExecutablePath(info_t *info, char *pathString, char *command)
{
    int currPos = 0;
    char *path;

    if (!pathString)
        return NULL;

    if ((strlen(command) > 2) && startsWith(command, "./"))
    {
        if (isExecutable(info, command))
            return command;
    }

    for (int i = 0;; i++)
    {
        if (!pathString[i] || pathString[i] == ':')
        {
            path = copyCharacters(pathString, currPos, i);
            if (!*path)
                strcat(path, command);
            else
            {
                strcat(path, "/");
                strcat(path, command);
            }
            if (isExecutable(info, path))
                return path;
            if (!pathString[i])
                break;
            currPos = i + 1;
        }
    }
    return NULL;
}

