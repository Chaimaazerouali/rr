#include "shell.h"

/**
 * my_eputs - prints an input string
 * @sr: the string to be printed
 *
 * Return: Nothing
 */
void my_eputs(char *sr)
{
int j = 0;

if (!sr)
return;
while (sr[j] != '\0')
{
my_eputchar(sr[j]);
j++;
}
}

/**
 * my_eputchar - writes the character c to stderr
 * @ch: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int my_eputchar(char ch)
{
static int j;
static char buf[MY_WRITE_BUF_SIZE];

if (ch == MY_BUF_FLUSH || j >= MY_WRITE_BUF_SIZE)
{
write(2, buf, j);
j = 0;
}
if (ch != MY_BUF_FLUSH)
buf[j++] = ch;
return (1);
}

/**
 * my_putfd - writes the character c to given fd
 * @ch: The character to print
 * @f: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int my_putfd(char ch, int f)
{
static int j;
static char buf[MY_WRITE_BUF_SIZE];

if (ch == MY_BUF_FLUSH || j >= MY_WRITE_BUF_SIZE)
{
write(f, buf, j);
j = 0;
}
if (ch != MY_BUF_FLUSH)
buf[j++] = ch;
return (1);
}

/**
 * my_putsfd - prints an input string
 * @sr: the string to be printed
 * @f: the file descriptor to write to
 *
 * Return: the number of chars put
 */
int my_putsfd(char *sr, int f)
{
int j = 0;

if (!sr)
return (0);
while (*sr)
{
j += my_putfd(*sr++, f);
}
return (j);
}

