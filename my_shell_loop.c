#include "shell.h"

/**
 * my_hsh - main shell loop
 * @in: the parameter & return info struct
 * @v: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int my_hsh(my_info_t *in, char **v)
{
ssize_t q = 0;
int b_ret = 0;

while (q != -1 && b_ret != -2)
{
clear_my_info(in);
if (my_interactive(in))
my_puts("$ ");
my_eputchar(MY_BUF_FLUSH);
q = get_my_input(in);
if (q != -1)
{
set_my_info(in, v);
b_ret = find_my_builtin(in);
if (b_ret == -1)
find_my_cmd(in);
}
else if (my_interactive(in))
my_putchar('\n');
free_my_info(in, 0);
}
write_my_history(in);
free_my_info(in, 1);
if (!my_interactive(in) && in->status)
exit(in->status);
if (b_ret == -2)
{
if (in->err_num == -1)
exit(in->status);
exit(in->err_num);
}
return (b_ret);
}

/**
 * find_my_builtin - finds a builtin command
 * @in: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int find_my_builtin(my_info_t *in)
{
int x, in_ret = -1;
my_builtin_table builtintbl[] = {
{"exit", my_exit},
{"env", my_env},
{"help", my_help},
{"history", my_history},
{"setenv", my_setenv},
{"unsetenv", my_unsetenv},
{"cd", my_cd},
{"alias", my_alias},
{NULL, NULL}
};

for (x = 0; builtintbl[x].type; x++)
if (my_strcmp(in->argv[0], builtintbl[x].type) == 0)
{
in->line_count++;
in_ret = builtintbl[x].func(in);
break;
}
return (in_ret);
}

/**
 * find_my_cmd - finds a command in PATH
 * @in: the parameter & return info struct
 *
 * Return: void
 */
void find_my_cmd(my_info_t *in)
{
char *path = NULL;
int x, k;

in->path = in->argv[0];
if (in->linecount_flag == 1)
{
in->line_count++;
in->linecount_flag = 0;
}
for (x = 0, k = 0; in->arg[x]; x++)
if (!my_is_delim(in->arg[x], " \t\n"))
k++;
if (!k)
return;

path = find_my_path(in, my_getenv(in, "PATH="), in->argv[0]);
if (path)
{
in->path = path;
fork_my_cmd(in);
}
else
{
if ((my_interactive(in) || my_getenv(in, "PATH=")
|| in->argv[0][0] == '/') && is_my_cmd(in, in->argv[0]))
fork_my_cmd(in);
else if (*(in->arg) != '\n')
{
in->status = 127;
print_my_error(in, "not found\n");
}
}
}

/**
 * fork_my_cmd - forks a an exec thread to run cmd
 * @in: the parameter & return info struct
 *
 * Return: void
 */
void fork_my_cmd(my_info_t *in)
{
pid_t child_pid;

child_pid = fork();
if (child_pid == -1)
{/* TODO: PUT ERROR FUNCTION */
perror("Error:");
return;
}
if (child_pid == 0)
{
if (execve(in->path, in->argv, get_my_environ(in)) == -1)
{
free_my_info(in, 1);
if (errno == EACCES)
exit(126);
exit(1);
 /* TODO: PUT ERROR FUNCTION */
}
else
{
wait(&(in->status));
if (WIFEXITED(in->status))
{
in->status = WEXITSTATUS(in->status);
if (in->status == 126)
print_my_error(in, "Permission denied\n");
}
}
}
}
