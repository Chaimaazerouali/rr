#include "shell.h"
/**
 * get_my_environ - returns the string array copy of our environ
 * @in: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
char **get_my_environ(my_info_t *in)
{
if (!in->my_environ || in->env_changed)
{
in->my_environ = my_list_to_strings(in->env);
in->env_changed = 0;
}

return (in->my_environ);
}

/**
 * my_unsetenv2 - Remove an environment variable
 * @in: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int my_unsetenv2(my_info_t *in, char *var)
{
my_list_t *node = in->env;
size_t j = 0;
char *p;

if (!node || !var)
return (0);

while (node)
{
p = my_starts_with(node->str, var);
if (p && *p == '=')
{
in->env_changed = delete_my_node_at_index(&(in->env), j);
j = 0;
node = in->env;
continue;
}
node = node->next;
j++;
}
return (in->env_changed);
}

/**
 * my_setenv2 - Initialize a new environment variable,
 * or modify an existing one
 * @in: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * @v: the string env var property
 * @va: the string env var value
 * Return: Always 0
 */
int my_setenv2(my_info_t *in, char *v, char *va)
{
char *b = NULL;
my_list_t *node;
char *p;

if (!v || !va)
return (0);

b = malloc(my_strlen(v) + my_strlen(va) + 2);
if (!b)
return (1);
my_strcpy(b, v);
my_strcat(b, "=");
my_strcat(b, va);
node = in->env;
while (node)
{
p = my_starts_with(node->str, v);
if (p && *p == '=')
{
free(node->str);
node->str = b;
in->env_changed = 1;
return (0);
}
node = node->next;
}
add_my_node_end(&(in->env), b, 0);
free(b);
in->env_changed = 1;
return (0);
}

