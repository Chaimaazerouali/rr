#include "shell.h"

/**
 * my_exit - exits the shell
 * @i: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int my_exit(my_info_t *i)
{
int exitcheck;

if (i->argv[1]) /* If there is an exit arguement */
{
exitcheck = my_erratoi(i->argv[1]);
if (exitcheck == -1)
{
i->status = 2;
print_my_error(i, "Illegal number: ");
my_eputs(i->argv[1]);
my_eputchar('\n');
return (1);
}
i->err_num = my_erratoi(i->argv[1]);
return (-2);
}
i->err_num = -1;
return (-2);
}

/**
 * my_cd - changes the current directory of the process
 * @in: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int my_cd(my_info_t *in)
{
char *s, *dir, buffer[1024];
int chdir_ret;

s = getcwd(buffer, 1024);
if (!s)
my_puts("TODO: >>getcwd failure emsg here<<\n");
if (!in->argv[1])
{
dir = my_getenv(in, "HOME=");
if (!dir)
chdir_ret = /* TODO: what should this be? */
chdir((dir = my_getenv(in, "PWD=")) ? dir : "/");
else
chdir_ret = chdir(dir);
}
else if (strcmp(in->argv[1], "-") == 0)
{
if (!my_getenv(in, "OLDPWD="))
{
my_puts(s);
my_putchar('\n');
return (1);
}
my_puts(my_getenv(in, "OLDPWD=")), my_putchar('\n');
chdir_ret = /* TODO: what should this be? */
chdir((dir = my_getenv(in, "OLDPWD=")) ? dir : "/");
}
else
chdir_ret = chdir(in->argv[1]);
if (chdir_ret == -1)
{
print_my_error(in, "can't cd to ");
my_eputs(in->argv[1]), my_eputchar('\n');
}
else
{
my_setenv2(in, "OLDPWD", my_getenv(in, "PWD="));
my_setenv2(in, "PWD", getcwd(buffer, 1024));
}
return (0);
}

/**
 * my_help - changes the current directory of the process
 * @i: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int my_help(my_info_t *i)
{
char **arg_array;

arg_array = i->argv;
my_puts("help call works. Function not yet implemented \n");
if (0)
my_puts(*arg_array); /* temp att_unused workaround */
return (0);
}

