#include "shell.h"

/**
 * my_strcpy - Transfers the contents of one string to another.
 * @dest: The target string.
 * @src: The string to be copied.
 *
 * Return: A pointer to the destination string.
 */
char *my_strcpy(char *dest, char *src)
{
int counter = 0;

if (dest == src || src == 0)
return (dest);
while (src[counter])
{
dest[counter] = src[counter];
counter++;
}
dest[counter] = 0;
return (dest);
}

/**
 * my_strdup - Produces a copy of the provided string.
 * @str: The string to be cloned.
 *
 * Return: A pointer to the newly cloned string.
 */
char *my_strdup(const char *str)
{
int strLength = 0;
char *newStr;

if (str == NULL)
return (NULL);
while (*str++)
strLength++;
newStr = malloc(sizeof(char) * (strLength + 1));
if (!newStr)
return (NULL);
for (strLength++; strLength--;)
newStr[strLength] = *--str;
return (newStr);
}

/**
 * my_puts - Outputs a string to the standard console.
 * @str: The string intended for display.
 *
 * Return: None.
 */
void my_puts(char *str)
{
int position = 0;

if (!str)
return;
while (str[position] != '\0')
{
my_putchar(str[position]);
position++;
}
}

/**
 * my_putchar - Outputs a character to the standard output.
 * @c: The character designated for display.
 *
 * Return: Returns 1 upon success. If an error occurs, -1 is returned.
 */
int my_putchar(char c)
{
static int bufPosition;
static char buf[MY_WRITE_BUF_SIZE];

if (c == MY_BUF_FLUSH || bufPosition >= MY_WRITE_BUF_SIZE)
{
write(1, buf, bufPosition);
bufPosition = 0;
}
if (c != MY_BUF_FLUSH)
buf[bufPosition++] = c;
return (1);
}
