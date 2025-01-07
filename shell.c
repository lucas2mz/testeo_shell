#include "main.h"
/**
 * main - Entry of the program
 *
 * Return: Always 0
 */
int main(void)
{
	char *path = _getenv("PATH");

	main_function(path);
	return (0);
}
