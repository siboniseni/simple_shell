#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
}
list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
}

info_t;

#define INFO_INIT 
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct shell_builtin
{
	char *type;
	int (*func)(info_t *);

	builtin_table;
}



/* toem_in_ext_commands.c */
int shell_loop(info_t *info, char **av);
int find_builtin(info_t *info);
void find_command(info_t *info);
void fork_command(info_t *info);


/* toem_path.c  */
int isexecutable(info_t *info, char *filePath)
char *copycharacters(char *source, int start, int stop)
char *findexecutablePath(info_t *info, char *pathString, char *command)

/* toem  */


/* toem__erratoi.c */
int _erratoi(char *s);
void print_error(info_t *info, char *estr);
int print_d(int input, int fd);
char *convert_number(long int num, int base, int flags);
void remove_comments(char *buf);

/* toem_string_utils.c  */
int str_length(char*)
int str_compare(char*, char*)
str_starts_with(const char *, const char *)
char *str_concatenate(char *, char *)

/* toem_str_manip_print_fun.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_tokenA.c*/
char **splitString(char*, char*)
char **strtow2(char*, char); 
char **splitString2(char *,char)

/* toem_opr_memory.c */
char *copy_string(char *destination, const char *source);
char *duplicate_string(const char *str);
void print_string(const char *str);
int print_character(char c);


/* toem_ com_hst.c*/
char *retrieve_history_file(info_t *info);
int save_history(info_t *info);
int load_history(info_t *info);
int create_history_entry(info_t *info, char *buf, int linecount);
int renumber_history_entries(info_t *info);


/* toem_ shell_interactive.c*/
int check_interactive(info_t *info);
int check_delim(char c, char *delim);
int check_alpha(int c);
int convert_to_int(char *s);


/* toem_conversion.c */
int erratoi(char*)
void printError(info_t*, char*) 
int printout_d(int, int)
char *convert_numb(long int, int, int)
void remove_comments(char*);

/* toem_shell_functions.c */
int my_exit(info_t*)
int my_cd(info_t*)
int my_help(info_t*)

/* toem_history_list.c */
int display_history(info_t *info);
int remove_alias(info_t *info, char *str);
int set_alias(info_t *info, char *str);
int print_alias(list_t *node);
int alias_builtin(info_t *info);

/*toem_input_handler.c */
ssize_t get_input(info_t *);
ssize_t input_bufr(info_t*, char**, size_t*)
ssize_t read_buf(info_t*, char*, size_t*) 
int _getline(info_t*, char**, size_t*);
void sigintHandler(int);

/* toem_getinfo.c */
void clearInfo(info_t *)
void setInfo(info_t *, char **)
void freeInfo(info_t *, int)


/* toem_env_functions.c*/
char *get_env(info_t *, const char *);
int my_env(info_t *);
int my_setenv((info_t *);
int my_unsetenv(info_t *);
int populate_env_list(info_t *);

/* toem_ environment_var.c*/
char **get_environment(info_t *info);
int unset_environment_variable(info_t *info, const char *variable);
int set_environment_variable(info_t *info, const char *variable, const char *value);


/* toem_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* toem_list_handling.c */
list_t *addNode(list_t **, const char *, int)
list_t *addNode_end(list_t **, const char *, int)
size_t print_list_str(const list_t *)
int delete_node_index(list_t **, unsigned int)
void free_list(list_t **)


/* toem_ memory_manag.c */
size_t count_list_nodes(const list_t *head);
char **convert_list_to_strings(list_t *head);
size_t print_linked_list(const list_t *head);
list_t *find_node_starts_with(list_t *head, char *prefix, char c);
ssize_t get_node_index(list_t *head, list_t *node);

/* toem_chain_delim_alis_var_rep.c */
int is_chain_delimiter(info_t *info, char *buffer, size_t *position);
void check_chain_continuation(info_t *info, char *buffer, size_t *position, size_t start, size_t length);
int replace_aliases(info_t *info);
int replace_variables(info_t *info);
int replace_string(char **old_string, char *new_string);

/*toem_info_utils.c*/
void clearInfo(info_t *info);
void setInfo(info_t *info, char **av);
void freeInfo(info_t *info, int all);

/*toem_lists_conv.c*/
int free_and_null(void **ptr);

/*toem_shell_interactive.c*/

void clearInfo(info_t *info);
void setInfo(info_t *info, char **av);
void freeInfo(info_t *info, int all);
int free_and_null(void **ptr);
int check_interactive(info_t *info);
int check_delim(char c, char *delim);
int check_alpha(int c);
int convert_to_int(char *s);

/*toem_environment_var*/
char **get_environment(info_t *info);
int unset_environment_variable(info_t *info, const char *variable);
int set_environment_variable(info_t *info, const char *variable, const char *value);


#endif
