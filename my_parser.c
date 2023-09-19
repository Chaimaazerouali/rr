#include "shell.h"

/**
 * is_my_cmd - checks if a file serves as an executable command.
 * @info: the info structure.
 * @path: file's path.
 *
 * Return: 1 if true, 0 otherwise.
 */
int is_my_cmd(my_info_t *info, char *path)
{
struct stat fileStatus;

(void)info;
if (!path || stat(path, &fileStatus))
return (0);

if (fileStatus.st_mode & S_IFREG)
{
return (1);
}
return (0);
}

/**
 * duplicate_chars - creates a copy of specified characters.
 * @pathstr: the PATH string.
 * @start: start position.
 * @stop: end position.
 *
 * Return: pointer to the newly allocated buffer.
 */
char *duplicate_chars(char *pathstr, int start, int stop)
{
static char buffer[1024];
int index = 0, iterator = 0;

for (iterator = 0, index = start; index < stop; index++)
if (pathstr[index] != ':')
buffer[iterator++] = pathstr[index];
buffer[iterator] = 0;
return (buffer);
}

/**
 * find_my_path - locates the command in the PATH string.
 * @info: the info structure.
 * @pathstr: the PATH string.
 * @cmd: the command to locate.
 *
 * Return: full path of command if located, or NULL.
 */
char *find_my_path(my_info_t *info, char *pathstr, char *cmd)
{
int index = 0, currentPosition = 0;
char *constructedPath;

if (!pathstr)
return (NULL);
if ((my_strlen(cmd) > 2) && my_starts_with(cmd, "./"))
{
if (is_my_cmd(info, cmd))
return (cmd);
}
while (1)
{
if (!pathstr[index] || pathstr[index] == ':')
{
constructedPath = duplicate_chars(pathstr, currentPosition, index);
if (!*constructedPath)
my_strcat(constructedPath, cmd);
else
{
my_strcat(constructedPath, "/");
my_strcat(constructedPath, cmd);
}
if (is_my_cmd(info, constructedPath))
return (constructedPath);
if (!pathstr[index])
break;
currentPosition = index;
}
index++;
}
return (NULL);
}
