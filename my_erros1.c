#include "shell.h"

/**
 * my_erratoi - converts a string to an integer
 * @sr: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int my_erratoi(char *sr)
{
int j = 0;
unsigned long int r = 0;

if (*sr == '+')
sr++;
for (j = 0; sr[j] != '\0'; j++)
{
if (sr[j] >= '0' && sr[j] <= '9')
{
r *= 10;
r += (sr[j] - '0');
if (r > INT_MAX)
return (-1);
}
else
return (-1);
}
return (r);
}

/**
 * print_my_error - prints an error message
 * @in: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_my_error(my_info_t *in, char *estr)
{
my_eputs(in->fname);
my_eputs(": ");
print_my_d(in->line_count, STDERR_FILENO);
my_eputs(": ");
my_eputs(in->argv[0]);
my_eputs(": ");
my_eputs(estr);
}

/**
 * print_my_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @f: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int print_my_d(int input, int f)
{
int (*my_putchar)(char) = my_putchar;
int j, c = 0;
unsigned int a, ct;

if (f == STDERR_FILENO)
my_putchar = my_eputchar;
if (input < 0)
{
a = -input;
my_putchar('-');
c++;
}
else
a = input;
ct = a;
for (j = 1000000000; j > 1; j /= 10)
{
if (a / j)
{
my_putchar('0' + ct / j);
c++;
}
ct %= j;
}
my_putchar('0' + ct);
c++;

return (c);
}
