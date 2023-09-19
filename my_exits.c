#include "shell.h"

/**
 * my_strncpy - copies a string
 * @dt: the destination string to be copied to
 * @sc: the source string
 * @m: the amount of characters to be copied
 * Return: the concatenated string
 */
char *my_strncpy(char *dt, char *sc, int m)
{
int i, j;
char *st = dt;

i = 0;
while (sc[i] != '\0' && i < m - 1)
{
dt[i] = sc[i];
i++;
}
if (i < m)
{
j = i;
while (j < m)
{
dt[j] = '\0';
j++;
}
}
return (st);
}

/**
 * my_strncat - concatenates two strings
 * @dt: the first string
 * @sc: the second string
 * @m: the amount of bytes to be maximally used
 * Return: the concatenated string
 */
char *my_strncat(char *dt, char *sc, int m)
{
int i, j;
char *sg = dt;

i = 0;
j = 0;
while (dt[i] != '\0')
i++;
while (sc[j] != '\0' && j < m)
{
dt[i] = sc[j];
i++;
j++;
}
if (j < m)
dt[i] = '\0';
return (sg);
}

/**
 * my_strchr - locates a character in a string
 * @sg: the string to be parsed
 * @ch: the character to look for
 * Return: (sg) a pointer to the memory area s
 */
char *my_strchr(char *sg, char ch)
{
do {
if (*sg == ch)
return (sg);
} while (*sg++ != '\0');

return (NULL);
}

