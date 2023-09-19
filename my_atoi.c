#include "shell.h"

/**
 * my_interactive - returns true if shell is interactive mode
 * @i: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int my_interactive(my_info_t *i)
{
return (isatty(STDIN_FILENO) && i->readfd <= 2);
}

/**
 * my_is_delim - checks if character is a delimiter
 * @ch: the char to check
 * @del: the delimiter string
 * Return: 1 if true, 0 if false
 */
int my_is_delim(char ch, char *del)
{
while (*del)
if (*del++ == ch)
return (1);
return (0);
}

/**
 * my_is_alpha - checks for alphabetic character
 * @ch: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int my_is_alpha(int ch)
{
if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
return (1);
else
return (0);
}

/**
 * my_atoi - converts a string to an integer
 * @sg: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int my_atoi(char *sg)
{
int i, sign = 1, flag = 0, output;
unsigned int result = 0;

for (i = 0; sg[i] != '\0' && flag != 2; i++)
{
if (sg[i] == '-')
sign *= -1;

if (sg[i] >= '0' && sg[i] <= '9')
{
flag =  1;
result *= 10;
result += (sg[i] - '0');
}
else if (flag == 1)
flag = 2;
}

if (sign == -1)
output = -result;
else
output = result;

return (output);
}

