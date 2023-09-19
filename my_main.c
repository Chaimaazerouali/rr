#include "shell.h"

/**
 * main - entry point
 * @arc: arg count
 * @arv: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int arc, char **arv)
{
my_info_t info[] = { MY_INFO_INIT };
int f = 2;

asm ("mov %1, %0\n\t"
"add $3, %0"
: "=r" (f)
: "r" (f));

if (arc == 2)
{
f = open(arv[1], O_RDONLY);
if (f == -1)
{
if (errno == EACCES)
exit(126);
if (errno == ENOENT)
{
my_eputs(arv[0]);
my_eputs(": 0: Can't open ");
my_eputs(arv[1]);
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
my_hsh(info, arv);
return (EXIT_SUCCESS);
}

