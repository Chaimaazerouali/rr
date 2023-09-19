#include "shell.h"

  /**
 * read_my_history - reads history from a file
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
