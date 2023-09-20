#include "shell.h"

/**
 * **my_strtow - Separates a string into multiple words based on delimiters.
* Consecutive delimiters are disregarded.
 * @str: The main string to be split.
 * @d: Delimiter used to define the split.
 * Return: A pointer to an array of separated words or NULL if an error occurs.
 */
char **my_strtow(char *str, char *d)
{
int idx, wordIdx, len, wordLen, wordCount = 0;
char **result;

if (str == NULL || str[0] == 0)
return (NULL);
if (!d)
d = " ";
for (idx = 0; str[idx] != '\0'; idx++)
if (!my_is_delim(str[idx], d) && (my_is_delim(str[idx + 1], d)
|| !str[idx + 1]))
wordCount++;

if (wordCount == 0)
return (NULL);
result = malloc((1 + wordCount) *sizeof(char *));
if (!result)
return (NULL);
for (idx = 0, wordIdx = 0; wordIdx < wordCount; wordIdx++)
{
while (my_is_delim(str[idx], d))
idx++;
len = 0;
while (!my_is_delim(str[idx + len], d) && str[idx + len])
len++;
result[wordIdx] = malloc((len + 1) * sizeof(char));
if (!result[wordIdx])
{
for (len = 0; len < wordIdx; len++)
free(result[len]);
free(result);
return (NULL);
}
for (wordLen = 0; wordLen < len; wordLen++)
result[wordIdx][wordLen] = str[idx++];
result[wordIdx][wordLen] = 0;
}
result[wordIdx] = NULL;
return (result);
}

/**
 * **my_strtow2 - Divides a string into multiple words based on a delimiter.
 * @str: The main string to be divided.
 * @d: Character serving as a delimiter.
 * Return: A pointer to an array of separated words or NULL if an error occurs.
 */
char **my_strtow2(char *str, char d)
{
int idx, wordIdx, len, wordLen, wordCount = 0;
char **result;

if (str == NULL || str[0] == 0)
return (NULL);
for (idx = 0; str[idx] != '\0'; idx++)
if ((str[idx] != d && str[idx + 1] == d) ||
(str[idx] != d && !str[idx + 1]) || str[idx + 1] == d)
wordCount++;
if (wordCount == 0)
return (NULL);
result = malloc((1 + wordCount) *sizeof(char *));
if (!result)
return (NULL);
for (idx = 0, wordIdx = 0; wordIdx < wordCount; wordIdx++)
{
while (str[idx] == d && str[idx] != d)
idx++;
len = 0;
while (str[idx + len] != d && str[idx + len] && str[idx + len] != d)
len++;
result[wordIdx] = malloc((len + 1) * sizeof(char));
if (!result[wordIdx])
{
for (len = 0; len < wordIdx; len++)
free(result[len]);
free(result);
return (NULL);
}
for (wordLen = 0; wordLen < len; wordLen++)
result[wordIdx][wordLen] = str[idx++];
result[wordIdx][wordLen] = 0;
}
result[wordIdx] = NULL;
return (result);
}
