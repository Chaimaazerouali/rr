#include "shell.h"

/**
 * my_hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int my_hsh(my_info_t *info, char **av)
{
    ssize_t r;
    int builtin_ret;

    clear_my_info(info);
    if (my_interactive(info))
        my_puts("$ ");
    my_eputchar(MY_BUF_FLUSH);
    r = get_my_input(info);
    if (r != -1)
    {
        set_my_info(info, av);
        builtin_ret = find_my_builtin(info);
        if (builtin_ret == -1)
            find_my_cmd(info);
    }
    else if (my_interactive(info))
        my_putchar('\n');
    free_my_info(info, 0);
    write_my_history(info);
    free_my_info(info, 1);
    if (!my_interactive(info) && info->status)
        exit(info->status);
    if (info->err_num == -1)
        exit(info->status);
    exit(info->err_num);
    return (info->status);  // Default return.
}

/**
 * find_my_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int find_my_builtin(my_info_t *info)
{
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
    int i;

    for (i = 0; builtintbl[i].type; i++)
    {
        if (my_strcmp(info->argv[0], builtintbl[i].type) == 0)
        {
            info->line_count++;
            return builtintbl[i].func(info);
        }
    }
    return -1;
}

/**
 * find_my_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_my_cmd(my_info_t *info)
{
    char *path;
    int i, k;

    info->path = info->argv[0];
    if (info->linecount_flag == 1)
    {
        info->line_count++;
        info->linecount_flag = 0;
    }
    for (i = 0, k = 0; info->arg[i]; i++)
        if (!my_is_delim(info->arg[i], " \t\n"))
            k++;
    if (!k)
        return;
    path = find_my_path(info, my_getenv(info, "PATH="), info->argv[0]);
    if (path)
    {
        info->path = path;
        fork_my_cmd(info);
    }
    else
    {
        if ((my_interactive(info) || my_getenv(info, "PATH=") || info->argv[0][0] == '/') && is_my_cmd(info, info->argv[0]))
            fork_my_cmd(info);
        else if (*(info->arg) != '\n')
        {
            info->status = 127;
            print_my_error(info, "not found\n");
        }
    }
}

/**
 * fork_my_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_my_cmd(my_info_t *info)
{
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == -1)
    {
        perror("Error:");
        return;
    }
    if (child_pid == 0)
    {
        if (execve(info->path, info->argv, get_my_environ(info)) == -1)
        {
            free_my_info(info, 1);
            if (errno == EACCES)
                exit(126);
            exit(1);
        }
    }
    else
    {
        wait(&(info->status));
        if (WIFEXITED(info->status))
        {
            info->status = WEXITSTATUS(info->status);
            if (info->status == 126)
                print_my_error(info, "Permission denied\n");
        }
    }
}
