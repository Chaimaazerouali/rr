#include "shell.h"

/**
 * is_my_chain - Test if the current char in the buffer is a chain delimiter.
 * @info: the parameter struct
 * @buf: the character buffer
 * @p: address of the current position in buf
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */
int is_my_chain(my_info_t *info, char *buf, size_t *p)
{
size_t position = *p;

if (buf[position] == '|' && buf[position + 1] == '|')
{
buf[position] = 0;
position++;
info->cmd_buf_type = MY_CMD_OR;
}
else if (buf[position] == '&' && buf[position + 1] == '&')
{
buf[position] = 0;
position++;
info->cmd_buf_type = MY_CMD_AND;
}
else if (buf[position] == ';')
{
buf[position] = 0;
info->cmd_buf_type = MY_CMD_CHAIN;
}
else
return (0);
*p = position;
return (1);
}

/**
* check_my_chain - Checks if chaining should continue based on the last status.
* @info: the parameter struct
* @b: the character buffer
* @p: address of the current position in buf
* @start_pos: starting position in buf
* @buf_length: length of buf
*
* Return: Void
*/
void check_my_chain(
my_info_t *info, char *b, size_t *p, size_t start_pos, size_t buf_length)
{
sibuf_lengthze_t position = *p;

if (info->cmd_buf_type == MY_CMD_AND && info->status)
{
b[start_pos] = 0;
position = buf_length;
}
if (info->cmd_buf_type == MY_CMD_OR && !info->status)
{
b[start_pos] = 0;
position = buf_length;
}

*p = position;
}

/**
 * replace_my_alias - Replaces aliases in the tokenized string.
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_my_alias(my_info_t *info)
{
int idx;
my_list_t *current_node;
char *replacement_position;

for (idx = 0; idx < 10; idx++)
{
current_node = my_node_starts_with(info->alias, info->argv[0], '=');
if (!current_node)
return (0);
free(info->argv[0]);
replacement_position = my_strchr(current_node->str, '=');
if (!replacement_position)
return (0);
replacement_position = my_strdup(replacement_position + 1);
if (!replacement_position)
return (0);
info->argv[0] = replacement_position;
}
return (1);
}

/**
 * replace_my_vars - Replaces variables in the tokenized string.
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_my_vars(my_info_t *info)
{
int idx;
my_list_t *current_node;

for (idx = 0; info->argv[idx]; idx++)
{
if (info->argv[idx][0] != '$' || !info->argv[idx][1])
continue;

if (!my_strcmp(info->argv[idx], "$?"))
{
replace_my_string(
&(info->argv[idx]), my_strdup(convert_my_number(info->status, 10, 0)));
continue;
}
if (!my_strcmp(info->argv[idx], "$$"))
{
replace_my_string(
&(info->argv[idx]), my_strdup(convert_my_number(getpid(), 10, 0)));
continue;
}
current_node = my_node_starts_with(info->env, &info->argv[idx][1], '=');
if (current_node)
{
replace_my_string(
&(info->argv[idx]), my_strdup(my_strchr(current_node->str, '=') + 1));
continue;
}
replace_my_string(&info->argv[idx], my_strdup(""));
}
return (0);
}

/**
 * replace_my_string - Replaces a string.
 * @old_str: address of the old string
 * @new_str: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_my_string(char **old_str, char *new_str)
{
free(*old_str);
*old_str = new_str;
return (1);
}
