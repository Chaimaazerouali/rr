#include "shell.h"
/**
 * get_my_history_file - gets the history file
 * @in: parameter struct
 *
 * Return: allocated string containing history file
 */

char *get_my_history_file(my_info_t *in)
{
char *a, *b;

b = my_getenv(in, "HOME=");
if (!b)
return (NULL);
a = malloc(sizeof(char) * (my_strlen(b) + my_strlen(MY_HIST_FILE) + 2));
if (!a)
return (NULL);
a[0] = 0;
my_strcpy(a, b);
my_strcat(a, "/");
my_strcat(a, MY_HIST_FILE);
return (a);
}

/**
 * write_my_history - creates a file or appends to an existing file
 * @in: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_my_history(my_info_t *in)
{
ssize_t f;
char *filename = get_my_history_file(in);
my_list_t *node = NULL;

if (!filename)
return (-1);

f = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filename);
if (f == -1)
return (-1);
for (node = in->history; node; node = node->next)
{
my_putsfd(node->str, f);
my_putfd('\n', f);
}
my_putfd(MY_BUF_FLUSH, f);
close(f);
return (1);
}

