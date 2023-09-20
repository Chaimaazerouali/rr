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
/**
* read_my_history - this function allow to read my history
* @in: the parameter struct
*
* Return: histcount on success, 0 otherwise
*/
int read_my_history(my_info_t *in)
{
int i, l = 0, lt = 0;
ssize_t f, rn, fs = 0;
struct stat st;
char *b = NULL, *filename = get_my_history_file(in);

if (!filename)
return (0);

f = open(filename, O_RDONLY);
free(filename);
if (f == -1)
return (0);
if (!fstat(f, &st))
fs = st.st_size;
if (fs < 2)
return (0);
b = malloc(sizeof(char) * (fs + 1));
if (!b)
return (0);
rn = read(f, b, fs);
b[fs] = 0;
if (rn <= 0)
return (free(b), 0);
close(f);
for (i = 0; i < fs; i++)
if (b[i] == '\n')
{
b[i] = 0;
build_my_history_list(in, b + l, lt++);
l = i + 1;
}
if (l != i)
build_my_history_list(in, b + l, lt++);
free(b);
in->histcount = lt;
while (in->histcount-- >= MY_HIST_MAX)
delete_my_node_at_index(&(in->history), 0);
renumber_my_history(in);
return (in->histcount);
}

/**
 * build_my_history_list - adds an entry to a history linked list
 * @in: Structure containing potential arguments. Used to maintain
 * @b: buffer
 * @lt: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_my_history_list(my_info_t *in, char *b, int lt)
{
my_list_t *node = NULL;

if (in->history)
node = in->history;
add_my_node_end(&node, b, lt);

if (!in->history)
in->history = node;
return (0);
}

/**
 * renumber_my_history - renumbers the history linked list after changes
 * @in: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_my_history(my_info_t *in)
{
my_list_t *node = in->history;
int x = 0;

while (node)
{
node->num = x++;
node = node->next;
}
return (in->histcount = x);
}
