#include "main.h"

int ejecutar_comando(char *full_path, char **args)
{
	extern char **environ;
	pid_t hijo;
	int status;

	hijo = fork();

	if (hijo == 0)
	{
		if (execve(full_path, args, environ) == -1)
		{
			perror("Execve");
			return (1);
		}
	}
	else
	{
		wait(&status);
	}
	return (0);
}
