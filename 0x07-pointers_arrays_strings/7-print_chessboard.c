#include "main.h"

/**
 * print_chessboard - prints chessboard
 *
 * @a: rows
 * Return: nothing
*/

void print_chessboard(char (*a)[8])
{
	int itr, jtr;

	for (itr = 0; itr < 8; jtr++)
	{
		_putchar(a[itr][jtr]);
	}
	_putchar('\n');
}
