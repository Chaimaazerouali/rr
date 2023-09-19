#include "shell.h"

/**
 * my_env - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int my_env(my_info_t *info)
{
print_my_list_str(info->env);
return (0);
}

/**
 * my_getenv - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *my_getenv(my_info_t *info, const char *name)
{
my_list_t *node = info->env;
char *p;

while (node)
{
p = my_starts_with(node->str, name);
if (p && *p)
return (p);
node = node->next;
}
return (NULL);
}

/**
 * my_setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int my_setenv(my_info_t *info)
{
if (info->argc != 3)
{
my_eputs("Incorrect number of arguements\n");
return (1);
}
if (my_setenv2(info, info->argv[1], info->argv[2]))
return (0);
return (1);
}

/**
 * my_unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int my_unsetenv(my_info_t *info)
{
int i;

if (info->argc == 1)
{
my_eputs("Too few arguements.\n");
return (1);
}
for (i = 1; i <= info->argc; i++)
my_unsetenv2(info, info->argv[i]);

return (0);
}

/**
 * populate_my_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_my_env_list(my_info_t *info)
{
my_list_t *node = NULL;
size_t i;

for (i = 0; environ[i]; i++)
add_my_node_end(&node, environ[i], 0);
info->env = node;
return (0);
}

