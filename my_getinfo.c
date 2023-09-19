#include "shell.h"
/**
 * clear_my_info - initializes info_t struct
 * @in: struct address
 */
void clear_my_info(my_info_t *in)
{
in->arg = NULL;
in->argv = NULL;
in->path = NULL;
in->argc = 0;
}

/**
 * set_my_info - initializes info_t struct
 * @in: struct address
 * @avr: argument vector
 */
void set_my_info(my_info_t *in, char **avr)
{
int x = 0;

in->fname = avr[0];
if (in->arg)
{
in->argv = my_strtow(in->arg, " \t");
if (!in->argv)
{
in->argv = malloc(sizeof(char *) * 2);
if (in->argv)
{
in->argv[0] = my_strdup(in->arg);
in->argv[1] = NULL;
}
}
for (x = 0; in->argv && in->argv[x]; x++)
;
in->argc = x;

replace_my_alias(in);
replace_my_vars(in);
}
}

/**
 * free_my_info - frees info_t struct fields
 * @in: struct address
 * @al: true if freeing all fields
 */
void  free_my_info(my_info_t *in, int al)
{
my_ffree(in->argv);
in->argv = NULL;
in->path = NULL;
if (al)
{
if (!in->cmd_buf)
free(in->arg);
if (in->env)
free_my_list(&(in->env));
if (in->history)
free_my_list(&(in->history));
if (in->alias)
free_my_list(&(in->alias));
my_ffree(in->my_environ);
in->my_environ = NULL;
my_bfree((void **)in->cmd_buf);
if (in->readfd > 2)
close(in->readfd);
my_putchar(MY_BUF_FLUSH);
}
}

