#include "shell.h"

/**
 * my_list_len - computes the number of elements in the linked list
 * @h: reference to the start node
 *
 * Return: quantity of elements in the list
 */
size_t my_list_len(const my_list_t *h)
{
size_t tally = 0;

while (h)
{
h = h->next;
tally++;
}
return (tally);
}

/**
 * my_list_to_strings - generates an array of strings using the list's str attributes
 * @head: reference to the start node
 *
 * Return: array of string elements
 */
char **my_list_to_strings(my_list_t *head)
{
my_list_t *currentNode = head;
size_t listLength = my_list_len(head), iter;
char **stringArray;
char *tempString;

if (!head || !listLength)
return (NULL);
stringArray = malloc(sizeof(char *) * (listLength + 1));
if (!stringArray)
return (NULL);
for (listLength = 0; currentNode; currentNode = currentNode->next, listLength++)
{
tempString = malloc(my_strlen(currentNode->str) + 1);
if (!tempString)
{
for (iter = 0; iter < listLength; iter++)
free(stringArray[iter]);
free(stringArray);
return (NULL);
}

tempString = my_strcpy(tempString, currentNode->str);
stringArray[listLength] = tempString;
}
stringArray[listLength] = NULL;
return (stringArray);
}

/**
 * print_my_list - displays each component of a my_list_t linked structure
 * @h: reference to the start node
 *
 * Return: number of elements in the structure
 */
size_t print_my_list(const my_list_t *h)
{
size_t tally = 0;

while (h)
{
my_puts(convert_my_number(h->num, 10, 0));
my_putchar(':');
my_putchar(' ');
my_puts(h->str ? h->str : "(nil)");
my_puts("\n");
h = h->next;
tally++;
}
return (tally);
}

/**
 * my_node_starts_with - identifies a node whose string commences with a designated prefix
 * @node: reference to my_list_t head
 * @prefix: string segment to identify
 * @c: character following the prefix to identify
 *
 * Return: node that matches or null
 */
my_list_t *my_node_starts_with(my_list_t *node, char *prefix, char c)
{
char *matchedStr = NULL;

while (node)
{
matchedStr = my_starts_with(node->str, prefix);
if (matchedStr && ((c == -1) || (*matchedStr == c)))
return (node);
node = node->next;
}
return (NULL);
}

/**
 * get_my_node_index - obtains the rank of a given node
 * @head: reference to my_list_t head
 * @node: reference to the desired node
 *
 * Return: position of the node or -1
 */
ssize_t get_my_node_index(my_list_t *head, my_list_t *node)
{
size_t tally = 0;

while (head)
{
if (head == node)
return (tally);
head = head->next;
tally++;
}
return (-1);
}
