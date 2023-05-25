#include "shell.h"

/**
 * retrieve_history_file - retrieves the history file path
 * @info: pointer to the information struct
 *
 * Return: allocated string containing the history file path
 */
char *retrieve_history_file(info_t *info)
{
    char *dir = get_env_variable(info, "HOME=");
    if (!dir)
        return NULL;

    char *path = allocate_memory(_str_len(dir) + _str_len(HIST_FILE) + 2);
    if (!path)
        return NULL;

    concat_strings(path, dir, "/");
    concat_strings(path, path, HIST_FILE);
    free(dir);

    return path;
}

/**
 * save_history - saves history to a file
 * @info: pointer to the information struct
 *
 * Return: 1 on success, -1 on failure
 */
int save_history(info_t *info)
{
    ssize_t fd;
    char *filename = retrieve_history_file(info);
    list_t *node = NULL;

    if (!filename)
        return -1;

    fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);
    if (fd == -1)
        return -1;

    for (node = info->history; node; node = node->next)
    {
        write_str_to_file(node->str, fd);
        write_char_to_file('\n', fd);
    }
    write_char_to_file(BUF_FLUSH, fd);

    close(fd);
    return 1;
}

/**
 * load_history - loads history from a file
 * @info: pointer to the information struct
 *
 * Return: number of history entries read, 0 on failure
 */
int load_history(info_t *info)
{
    int i, last = 0, linecount = 0;
    ssize_t fd, rdlen, fsize = 0;
    struct stat st;
    char *buf = NULL, *filename = retrieve_history_file(info);

    if (!filename)
        return 0;

    fd = open(filename, O_RDONLY);
    free(filename);
    if (fd == -1)
        return 0;

    if (!fstat(fd, &st))
        fsize = st.st_size;

    if (fsize < 2)
        return 0;

    buf = allocate_memory(fsize + 1);
    if (!buf)
        return 0;

    rdlen = read(fd, buf, fsize);
    buf[fsize] = '\0';

    if (rdlen <= 0)
        return free(buf), 0;

    close(fd);

    for (i = 0; i < fsize; i++)
    {
        if (buf[i] == '\n')
        {
            buf[i] = '\0';
            create_history_entry(info, buf + last, linecount++);
            last = i + 1;
        }
    }

    if (last != i)
        create_history_entry(info, buf + last, linecount++);

    free(buf);
    info->hist_count = linecount;

    while (info->hist_count-- >= HIST_MAX)
        delete_history_entry(&(info->history), 0);

    renumber_history_entries(info);
    return info->hist_count;
}

/**
 * create_history_entry - creates a history entry and adds it to the list
 * @info: pointer to the information struct
 * @buf: string buffer containing the history entry
 * @linecount: line count of the history entry
 *
 * Return: Always 0
 */
int create_history_entry(info_t *info, char *buf, int linecount)
{
    list_t *node = NULL;

    if (info->history)
        node = info->history;

    add_history_entry(&node, buf, linecount);

    if (!info->history)
        info->history = node;

    return 0;
}

/**
 * renumber_history_entries - renumbers the history entries after changes
 * @info: pointer to the information struct
 *
 * Return: the new hist_count
 */
int renumber_history_entries(info_t *info)
{
    list_t *node = info->history;
    int i = 0;

    while (node)
    {
        node->num = i++;
        node = node->next;
    }

    return (info->hist_count = i);
}
