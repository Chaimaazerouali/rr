#include "shell.h"

/**
 * my_bfree - frees a pointer and NULLs the address
 * @p: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int my_bfree(void **p)
{
if (p && *p)
{
free(*p);
*p = NULL;
return (1);
}
return (0);
}

