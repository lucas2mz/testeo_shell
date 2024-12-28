#include "main.h"

int main(int ac, char **av)
{
	char *linea, *path = _getenv("PATH"), *full_path;
	size_t size = 0;
	ssize_t len = 0;
	char **args;
	int i, status;
	pid_t hijo;

	while (1)
	{
		printf("Shellzilla$ ");
		len = getline(&linea, &size, stdin);
		if (len == -1)
		{
			break;
		}
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
			free(args);
			continue;
		}
		hijo = fork();
		if (hijo == 0)
		{
			if (execve(full_path, args, NULL) == -1)
			{
				perror("Execve");
				free(full_path);
				free(args);
				free(linea);
				return(1);
			}
		}
		else
		{
			wait(&status);
		}
		free(full_path);
		free(args);
	}
	free(linea);
	return (0);
}
