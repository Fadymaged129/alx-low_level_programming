#include <stdio.h>
/**
 * main - function
 *
 * Return - (0) always
 * Description - print lowercase alphabet
 */

int main(void)
{
	char ch = 'a';

	while (ch <= 'z')
	{
		putchar(ch);
		ch++;
	}

	putchar('\n');

	return (0);
}
