#include "shell.h"

/**
 * my_history - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @i: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int my_history(my_info_t *i)
{
print_my_list(i->history);
return (0);
}

/**
 *  unset_alias - sets alias to string
 * @i: parameter struct
 * @sr: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int  unset_alias(my_info_t *i, char *sr)
{
char *a, b;
int rt;

a = my_strchr(sr, '=');
if (!a)
return (1);
b = *a;
*a = 0;
rt = delete_my_node_at_index(&(i->alias),
get_my_node_index(i->alias, my_node_starts_with(i->alias, sr, -1)));
*a = b;
return (rt);
}

/**
 * set_alias - sets alias to string
 * @i: parameter struct
 * @sr: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(my_info_t *i, char *sr)
{
char *a;

a = my_strchr(sr, '=');
if (!a)
return (1);
if (!*++a)
return (unset_alias(i, sr));

unset_alias(i, sr);
return (add_my_node_end(&(i->alias), sr, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(my_list_t *node)
{
char *a = NULL, *z = NULL;

if (node)
{
a = my_strchr(node->str, '=');
for (z = node->str; z <= a; z++)
my_putchar(*z);
my_putchar('\'');
my_puts(a + 1);
my_puts("'\n");
return (0);
}
return (1);
}

/**
 * my_alias - mimics the alias builtin (man alias)
 * @i: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int my_alias(my_info_t *i)
{
int q = 0;
char *a = NULL;
my_list_t *node = NULL;

if (i->argc == 1)
{
node = i->alias;
while (node)
{
print_alias(node);
node = node->next;
}
return (0);
}
for (q = 1; i->argv[q]; q++)
{
a = my_strchr(i->argv[q], '=');
if (a)
set_alias(i, i->argv[q]);
else
print_alias(my_node_starts_with(i->alias, i->argv[q], '='));
}

return (0);
}

