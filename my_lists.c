#include "shell.h"

/**
 * add_my_node - Appends a node to the beginning of the list
 * @head: pointer reference to the initial node
 * @str: string element of the node
 * @num: index of the node used by history
 *
 * Return: size of the list
 */
my_list_t *add_my_node(my_list_t **head, const char *str, int num)
{
my_list_t *new_entry;

if (!head)
return (NULL);
new_entry = malloc(sizeof(my_list_t));
if (!new_entry)
return (NULL);
my_memset((void *)new_entry, 0, sizeof(my_list_t));
new_entry->num = num;
if (str)
{
new_entry->str = my_strdup(str);
if (!new_entry->str)
{
free(new_entry);
return (NULL);
}
}
new_entry->next = *head;
*head = new_entry;
return (new_entry);
}

/**
 * add_my_node_end - Appends a node at the tail of the list
 * @head: pointer reference to the initial node
 * @str: string element of the node
 * @num: index of the node used by history
 *
 * Return: size of the list
 */
my_list_t *add_my_node_end(my_list_t **head, const char *str, int num)
{
my_list_t *new_tail, *current_node;

if (!head)
return (NULL);

current_node = *head;
new_tail = malloc(sizeof(my_list_t));
if (!new_tail)
return (NULL);
my_memset((void *)new_tail, 0, sizeof(my_list_t));
new_tail->num = num;
if (str)
{
new_tail->str = my_strdup(str);
if (!new_tail->str)
{
free(new_tail);
return (NULL);
}
}
if (current_node)
{
while (current_node->next)
current_node = current_node->next;
current_node->next = new_tail;
}
else
*head = new_tail;
return (new_tail);
}

/**
 * print_my_list_str - Outputs only the str elmnt of a my_list_t linked list
 * @h: pointer to the foremost node
 *
 * Return: size of the list
 */
size_t print_my_list_str(const my_list_t *h)
{
size_t count = 0;

while (h)
{
my_puts(h->str ? h->str : "(nil)");
my_puts("\n");
h = h->next;
count++;
}
return (count);
}

/**
 * delete_my_node_at_index - Removes the node at a specified index
 * @head: pointer reference to the foremost node
 * @idx: position of the node to eliminate
 *
 * Return: 1 if successful, 0 if not
 */
int delete_my_node_at_index(my_list_t **head, unsigned int idx)
{
my_list_t *current, *previous_node;
unsigned int i = 0;

if (!head || !*head)
return (0);

if (!idx)
{
current = *head;
*head = (*head)->next;
free(current->str);
free(current);
return (1);
}
current = *head;
while (current)
{
if (i == idx)
{
previous_node->next = current->next;
free(current->str);
free(current);
return (1);
}
i++;
previous_node = current;
current = current->next;
}
return (0);
}

/**
 * free_my_list - Liberates all nodes of a my_list_t list
 * @list_ref: pointer reference to the foremost node
 *
 * Return: void
 */
void free_my_list(my_list_t **list_ref)
{
my_list_t *current_node, *next_item, *list_head;

if (!list_ref || !*list_ref)
return;
list_head = *list_ref;
current_node = list_head;
while (current_node)
{
next_item = current_node->next;
free(current_node->str);
free(current_node);
current_node = next_item;
}
*list_ref = NULL;
}
