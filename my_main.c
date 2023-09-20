#include "shell.h"

/**
 * main - entry point
 * @c: arg count
 * @v: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int c, char **v)
{
my_info_t info[] = { MY_INFO_INIT };
int f = 2;

asm ("mov %1, %0\n\t"
"add $3, %0"
: "=r" (f)
: "r" (f));

if (c == 2)
{
f = open(v[1], O_RDONLY);
if (f == -1)
{
if (errno == EACCES)
exit(126);
if (errno == ENOENT)
{
my_eputs(v[0]);
my_eputs(": 0: Can't open ");
my_eputs(v[1]);
my_eputchar('\n');
my_eputchar(MY_BUF_FLUSH);
exit(127);
}
return (EXIT_FAILURE);
}
info->readfd = f;
}
populate_my_env_list(info);
read_my_history(info);
my_hsh(info, v);
return (EXIT_SUCCESS);
}

