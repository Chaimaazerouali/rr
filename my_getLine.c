#include "shell.h"

/**
 * input_buffer - buffers chained commands
 * @i: parameter struct
 * @b: address of buffer
 * @l: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buffer(my_info_t *i, char **b, size_t *l)
{
ssize_t rr = 0;
size_t len_p = 0;

if (!*l) /* if nothing left in the buffer, fill it */
{
/* bfree((void **)info->cmd_buf); */
free(*b);
*b = NULL;
signal(SIGINT, sigintHandler);
#if MY_USE_GETLINE
rr = getline(buf, &len_p, stdin);
#else
rr = my_getline(i, b, &len_p);
#endif
if (rr > 0)
{
if ((*b)[rr - 1] == '\n')
{
(*b)[rr - 1] = '\0';/* remove trailing newline */
rr--;

}
i->linecount_flag = 1;
remove_my_comments(*b);
build_my_history_list(i, *b, i->histcount++);
/* if (_strchr(*buf, ';')) is this a command chain? */
{
*l = rr;
i->cmd_buf = b;
}
}
}
return (rr);
}

/**
 * get_my_input - gets a line minus the newline
 * @in: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_my_input(my_info_t *in)
{
static char *b; /* the ';' command chain buffer */
static size_t i, j, l;
ssize_t rr = 0;
char **buf_p = &(in->arg), *p;

my_putchar(MY_BUF_FLUSH);
rr = input_buffer(in, &b, &l);
if (rr == -1) /* EOF */
return (-1);
if (l) /* we have commands left in the chain buffer */
{
j = i; /* init new iterator to current buf position */
p = b + i; /* get pointer for return */

check_my_chain(in, b, &j, i, l);
while (j < l) /* iterate to semicolon or end */
{
if (is_my_chain(in, b, &j))
break;
j++;
}

i = j + 1; /* increment past nulled ';'' */
if (i >= l) /* reached end of buffer? */
{
i = l = 0; /* reset position and length */
in->cmd_buf_type = MY_CMD_NORM;
}
*buf_p = p; /* pass back pointer to current command position */
return (my_strlen(p)); /* return length of current command */
}

*buf_p = b; /* else not a chain, pass back buffer from my_getline() */
return (rr); /* return length of buffer from my_getline() */
}


