#include "main.h"
/*
 * main - Entry of the program
 *
 * Return: Always 0
 */
int main(void)
{
	char *linea = NULL, *path = _getenv("PATH"), *full_path = NULL;
	char **args;
	
	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("Shellzilla$ ");
	
		if (leer_linea(&linea) == 0)
			break;

		args = tokenizar(linea, " \n\t");
		if (args == NULL || args[0] == NULL)
		{
			free(args);
			continue;
		}
		full_path = check_command(args[0], path);
		if (full_path == NULL)
		{
			printf("Shellzilla: No such file or directory\n");
			limpiar(linea, args, full_path);
			continue;
		}
		ejecutar_comando(full_path, args);
		limpiar(linea, args, full_path);
	}
	free(linea);
	return (0);
}
