#include "shell.h"

/**
 * my_memset - Fills a memory block with a specified byte.
 * @s: Pointer to the memory area.
 * @b: The byte to fill the memory with.
 * @n: Number of bytes to be filled.
 * Return: Pointer to the filled memory area.
 */
char *my_memset(char *s, char b, unsigned int n)
{
unsigned int idx;

for (idx = 0; idx < n; idx++)
s[idx] = b;

return (s);
}

/**
 * my_ffree - Frees a pointer to an array of strings.
 * @pp: Pointer to an array of strings.
 */
void my_ffree(char **pp)
{
char **origin = pp;

if (!pp)
return;

while (*pp)
free(*pp++);

free(origin);
}

/**
 * my_realloc - Reallocates a memory block.
 * @ptr: Pointer to the previously allocated block.
 * @old_size: Size of the previous memory block.
 * @new_size: Size desired for the new memory block.
 *
 * Return: Pointer to the reallocated memory block.
 */
void *my_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
char *new_block;

if (!ptr)
return (malloc(new_size));

if (!new_size)
{
free(ptr);
return (NULL);
}

if (new_size == old_size)
return (ptr);

new_block = malloc(new_size);

if (!new_block)
return (NULL);

old_size = old_size < new_size ? old_size : new_size;

for (unsigned int i = 0; i < old_size; i++)
new_block[i] = ((char *)ptr)[i];

free(ptr);
return (new_block);
}
