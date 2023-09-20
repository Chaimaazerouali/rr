#include "shell.h"
/**
 * my_list_len - determines length of linked list
 * @p: pointer to first node
 *
 * Return: size of list
 */
size_t my_list_len(const my_list_t *p)
{
size_t x = 0;

while (p)
{
p = p->next;
x++;
}
return (x);
}

/**
 * my_list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **my_list_to_strings(my_list_t *head)
{
my_list_t *node = head;
size_t x= my_list_len(head), j;
char **s;
char *sr;

if (!head || !x)
return (NULL);
s = malloc(sizeof(char *) * (x + 1));
if (!s)
return (NULL);
for (x = 0; node; node = node->next, x++)
{
sr = malloc(my_strlen(node->str) + 1);
if (!sr)
{
for (j = 0; j < x; j++)
free(s[j]);
free(s);
return (NULL);
}

sr = my_strcpy(sr, node->str);
s[x] = sr;
}
s[x] = NULL;
return (s);
}

/**
 * print_my_list - prints all elements of a my_list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_my_list(const my_list_t *h)
{
size_t x = 0;

while (h)
{
my_puts(convert_my_number(h->num, 10, 0));
my_putchar(':');
my_putchar(' ');
my_puts(h->str ? h->str : "(nil)");
my_puts("\n");
h = h->next;
x++;
}
return (x);
}

/**
 * my_node_starts_with - returns node whose string starts with prefix
 * @node: pointer to my_list_t head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
my_list_t *my_node_starts_with(my_list_t *node, char *prefix, char c)
{
char *p = NULL;

while (node)
{
p = my_starts_with(node->str, prefix);
if (p && ((c == -1) || (*p == c)))
return (node);
node = node->next;
}
return (NULL);
}

/**
 * get_my_node_index - gets the index of a node
 * @head: pointer to my_list_t head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_my_node_index(my_list_t *head, my_list_t *node)
{
size_t x = 0;

while (head)
{
if (head == node)
return (x);
head = head->next;
x++;
}
return (-1);
}

