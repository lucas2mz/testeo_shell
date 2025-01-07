#include "main.h"
/**
 * ejecutar_comando - Executes command
 * @full_path: The command to execute
 * @args: Array null terminated
 *
 * Return: Always 0
 */
int ejecutar_comando(char *full_path, char **args)
{
	pid_t hijo;
	int status;

	hijo = fork();

	if (hijo == -1)
	{
		perror("Fork");
		return (1);
	}

	if (hijo == 0)
	{
		if (execve(full_path, args, environ) == -1)
		{
			perror("Execve");
			exit(127);
		}
	}
	else
	{
		wait(&status);
	}
	return (0);
}
