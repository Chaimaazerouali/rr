#include "shell.h"

/**
 * my_strlen - Calculate the length of a provided string.
 * @str: the target string.
 *
 * Return: the count of characters in the string.
 */
int my_strlen(char *str)
{
int lengthCounter = 0;

if (!str)
return (0);

while (*str++)
lengthCounter++;
return (lengthCounter);
}

/**
 * my_strcmp - Compare two strings lexicographically.
 * @firstString: the first input string.
 * @secondString: the second input string.
 *
 * Return: negative if firstString < secondString, positive if firstString > secondString, zero if firstString == secondString.
 */
int my_strcmp(char *firstString, char *secondString)
{
while (*firstString && *secondString)
{
if (*firstString != *secondString)
return (*firstString - *secondString);
firstString++;
secondString++;
}
if (*firstString == *secondString)
return (0);
else
return (*firstString < *secondString ? -1 : 1);
}

/**
 * my_starts_with - Determine if a string starts with a specific substring.
 * @baseStr: the main string to search within.
 * @subStr: the target substring.
 *
 * Return: pointer to the next character after the substring in baseStr or NULL if not found.
 */
char *my_starts_with(const char *baseStr, const char *subStr)
{
while (*subStr)
if (*subStr++ != *baseStr++)
return (NULL);
return ((char *)baseStr);
}

/**
 * my_strcat - Append one string to the end of another.
 * @destination: the buffer to append to.
 * @source: the string to append.
 *
 * Return: pointer to the modified destination buffer.
 */
char *my_strcat(char *destination, char *source)
{
char *finalString = destination;

while (*destination)
destination++;
while (*source)
*destination++ = *source++;
*destination = *source;
return (finalString);
}
