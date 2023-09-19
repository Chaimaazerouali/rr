#include "shell.h"

/**
 * read_buffer - reads a buffer
 * @i: parameter struct
 * @b: buffer
 * @j: size
 *
 * Return: rr
 */
ssize_t read_buffer(my_info_t *i, char *b, size_t *j)
{
ssize_t rr = 0;

if (*j)
return (0);
rr = read(i->readfd, b, MY_READ_BUF_SIZE);
if (rr >= 0)
*j = rr;
return (rr);
}

/**
 * my_getline - gets the next line of input from STDIN
 * @i: parameter struct
 * @pr: address of pointer to buffer, preallocated or NULL
 * @lg: size of preallocated ptr buffer if not NULL
 *
 * Return: sm
 */
int my_getline(my_info_t *i, char **pr, size_t *lg)
{
static char b[MY_READ_BUF_SIZE];
static size_t j, l;
size_t k;
ssize_t r = 0, sm = 0;
char *p = NULL, *new_p = NULL, *c;

p = *pr;
if (p && lg)
sm = *lg;
if (j == l)
j = l = 0;

r = read_buffer(i, b, &l);
if (r == -1 || (r == 0 && l == 0))
return (-1);
c = my_strchr(b + j, '\n');
k = c ? 1 + (unsigned int)(c - b) : l;
new_p = my_realloc(p, sm, sm ? sm + k : k + 1);
if (!new_p) /* MALLOC FAILURE! */
return (p ? free(p), -1 : -1);

if (sm)
my_strncat(new_p, b + j, k - j);
else
my_strncpy(new_p, b + j, k - j + 1);

sm += k - j;
j = k;
p = new_p;

if (lg)
*lg = sm;
*pr = p;
return (sm);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sm: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sm)
{
my_puts("\n");
my_puts("$ ");
my_putchar(MY_BUF_FLUSH);
}
