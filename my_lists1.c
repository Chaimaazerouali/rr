#include "shell.h"

/**
 * my_list_len - calculates the size of the linked list
 * @h: reference to the first node
 *
 * Return: length of the list
 */
size_t my_list_len(const my_list_t *h)
{
size_t counter = 0;

while (h)
{
h = h->next;
counter++;
}
return (counter);
}

/**
 * my_list_to_strings - creates an array of strings from the list's str values
 * @head: reference to the first node
 *
 * Return: string array
 */
char **my_list_to_strings(my_list_t *head)
{
my_list_t *current = head;
size_t len = my_list_len(head), k;
char **arr_str;
char *temp_str;

if (!head || !len)
return (NULL);
arr_str = malloc(sizeof(char *) * (len + 1));
if (!arr_str)
return (NULL);
for (len = 0; current; current = current->next, len++)
{
temp_str = malloc(my_strlen(current->str) + 1);
if (!temp_str)
{
for (k = 0; k < len; k++)
free(arr_str[k]);
free(arr_str);
return (NULL);
}

temp_str = my_strcpy(temp_str, current->str);
arr_str[len] = temp_str;
}
arr_str[len] = NULL;
return (arr_str);
}

/**
 * print_my_list - outputs every element of a my_list_t linked list
 * @h: reference to the first node
 *
 * Return: length of the list
 */
size_t print_my_list(const my_list_t *h)
{
size_t counter = 0;

while (h)
{
my_puts(convert_my_number(h->num, 10, 0));
my_putchar(':');
my_putchar(' ');
my_puts(h->str ? h->str : "(nil)");
my_puts("\n");
h = h->next;
counter++;
}
return (counter);
}

/**
 * my_node_starts_with - finds a node with a string beginning with a specific prefix
 * @node: reference to my_list_t head
 * @prefix: string segment to look for
 * @c: subsequent character after the prefix to match
 *
 * Return: matching node or null
 */
my_list_t *my_node_starts_with(my_list_t *node, char *prefix, char c)
{
char *sub_str = NULL;

while (node)
{
sub_str = my_starts_with(node->str, prefix);
if (sub_str && ((c == -1) || (*sub_str == c)))
return (node);
node = node->next;
}
return (NULL);
}

/**
 * get_my_node_index - retrieves the position of a specific node
 * @head: reference to my_list_t head
 * @node: reference to the target node
 *
 * Return: node's position or -1
 */
ssize_t get_my_node_index(my_list_t *head, my_list_t *node)
{
size_t counter = 0;

while (head)
{
if (head == node)
return (counter);
head = head->next;
counter++;
}
return (-1);
}
