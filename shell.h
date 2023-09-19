#ifndef _MY_SHELL_H_
#define _MY_SHELL_H_

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
#define MY_READ_BUF_SIZE 1024
#define MY_WRITE_BUF_SIZE 1024
#define MY_BUF_FLUSH -1

/* for command chaining */
#define MY_CMD_NORM	0
#define MY_CMD_OR	1
#define MY_CMD_AND	2
#define MY_CMD_CHAIN	3

/* for convert_number() */
#define MY_CONVERT_LOWERCASE	1
#define MY_CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define MY_USE_GETLINE 0
#define MY_USE_STRTOK 0

#define MY_HIST_FILE	".my_shell_history"
#define MY_HIST_MAX	4096

extern char **environ;

/**
 * struct my_liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct my_liststr
{
	int num;
	char *str;
	struct my_liststr *next;
} my_list_t;

/**
 * struct my_passinfo - contains pseudo-arguments to pass into a function,
 * allowing a uniform prototype for a function pointer struct
 * @arg: a string generated from getline containing arguments
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @history: the history node
 * @alias: the alias node
 * @my_environ: custom modified copy of environ from LL env
 * @env_changed: on if my_environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd ; chain buffer, for memory management
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct my_passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	my_list_t *env;
	my_list_t *history;
	my_list_t *alias;
	char **my_environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory management */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} my_info_t;

#define MY_INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct my_builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct my_builtin
{
	char *type;
	int (*func)(my_info_t *);
} my_builtin_table;

/* my_shloop.c */
int my_hsh(my_info_t *, char **);
int find_my_builtin(my_info_t *);
void find_my_cmd(my_info_t *);
void fork_my_cmd(my_info_t *);

/* my_parser.c */
int is_my_cmd(my_info_t *, char *);
char *duplicate_chars(char *, int, int);
char *find_my_path(my_info_t *, char *, char *);

/* myloopsh.c */
int my_loopsh(char **);

/* my_errors.c */
void my_eputs(char *);
int my_eputchar(char);
int my_putfd(char c, int fd);
int my_putsfd(char *str, int fd);

/* my_string.c */
int my_strlen(char *);
int my_strcmp(char *, char *);
char *my_starts_with(const char *, const char *);
char *my_strcat(char *, char *);

/* my_string1.c */
char *my_strcpy(char *, char *);
char *my_strdup(const char *);
void my_puts(char *);
int my_putchar(char);

/* my_exits.c */
char *my_strncpy(char *, char *, int);
char *my_strncat(char *, char *, int);
char *my_strchr(char *, char);

/* my_tokenizer.c */
char **my_strtow(char *, char *);
char **my_strtow2(char *, char);

/* my_realloc.c */
char *my_memset(char *, char, unsigned int);
void my_ffree(char **);
void *my_realloc(void *, unsigned int, unsigned int);

/* my_memory.c */
int my_bfree(void **);

/* my_atoi.c */
int my_interactive(my_info_t *);
int my_is_delim(char, char *);
int my_is_alpha(int);
int my_atoi(char *);

/* my_errors1.c */
int my_erratoi(char *);
void print_my_error(my_info_t *, char *);
int print_my_d(int, int);
char *convert_my_number(long int, int, int);
void remove_my_comments(char *);

/* my_builtin.c */
int my_exit(my_info_t *);
int my_cd(my_info_t *);
int my_help(my_info_t *);

/* my_builtin1.c */
int my_history(my_info_t *);
int my_alias(my_info_t *);

/* my_getline.c */
ssize_t get_my_input(my_info_t *);
int my_getline(my_info_t *, char **, size_t *);
void sigintHandler(int);

/* my_getinfo.c */
void clear_my_info(my_info_t *);
void set_my_info(my_info_t *, char **);
void free_my_info(my_info_t *, int);

/* my_environ.c */
char *my_getenv(my_info_t *, const char *);
int my_env(my_info_t *);
int my_setenv(my_info_t *);
int my_unsetenv(my_info_t *);
int populate_my_env_list(my_info_t *);

/* my_getenv.c */
char **get_my_environ(my_info_t *);
int my_unsetenv2(my_info_t *, char *);
int my_setenv2(my_info_t *, char *, char *);

/* my_history.c */
char *get_my_history_file(my_info_t *info);
int write_my_history(my_info_t *info);
int read_my_history(my_info_t *info);
int build_my_history_list(my_info_t *info, char *buf, int linecount);
int renumber_my_history(my_info_t *info);

/* my_lists.c */
my_list_t *add_my_node(my_list_t **, const char *, int);
my_list_t *add_my_node_end(my_list_t **, const char *, int);
size_t print_my_list_str(const my_list_t *);
int delete_my_node_at_index(my_list_t **, unsigned int);
void free_my_list(my_list_t **);

/* my_lists1.c */
size_t my_list_len(const my_list_t *);
char **my_list_to_strings(my_list_t *);
size_t print_my_list(const my_list_t *);
my_list_t *my_node_starts_with(my_list_t *, char *, char);
ssize_t get_my_node_index(my_list_t *, my_list_t *);

/* my_vars.c */
int is_my_chain(my_info_t *, char *, size_t *);
void check_my_chain(my_info_t *, char *, size_t *, size_t, size_t);
int replace_my_alias(my_info_t *);
int replace_my_vars(my_info_t *);
int replace_my_string(char **, char *);

#endif

