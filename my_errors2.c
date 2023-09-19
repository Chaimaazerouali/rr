#include "shell.h"

/**
 * convert_my_number - converter function, a clone of itoa
 * @nm: number
 * @b: base
 * @fl: argument flags
 *
 * Return: string
 */
char *convert_my_number(long int nm, int b, int fl)
{
static char *array;
static char buffer[50];
char sign = 0;
char *ptr;
unsigned long n = nm;

if (!(fl & MY_CONVERT_UNSIGNED) && nm < 0)
{
n = -nm;
sign = '-';
}
array = fl & MY_CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
ptr = &buffer[49];
*ptr = '\0';

do {
*--ptr = array[n % b];
n /= b;
} while (n != 0);

if (sign)
*--ptr = sign;
return (ptr);
}

/**
 * remove_my_comments - function replaces first instance of '#' with '\0'
 * @b: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_my_comments(char *b)
{
int j;

for (j = 0; b[j] != '\0'; j++)
if (b[j] == '#' && (!j || b[j - 1] == ' '))
{
b[j] = '\0';
break;
}
}
