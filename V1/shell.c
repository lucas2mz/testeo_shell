#include "main.h"

int main(int ac, char **av)
{
	char *linea, *token, *full_path, *path = _getenv("PATH");
	size_t size = 0;
	ssize_t len = 0;
	char **args = malloc(sizeof(char *) * 1024);
	pid_t hijo;
	int i, status;

	while (1)
	{
		printf("Shellzilla$ ");
		len = getline(&linea, &size, stdin);

		if (len == -1)
		{
			break;
		}

		token = strtok(linea, " \n\t");

		i = 0;

		while (token != NULL)
		{
			args[i] = token;
			token = strtok(NULL, " \n\t");
			i++;
		}
		args[i] = NULL;

		full_path = check_command(args[0], path);

		if (full_path == NULL)
		{
			printf("Shellzilla: No such file or directory\n");
			continue;
		}

		hijo = fork();

		if (hijo == 0)
		{
			if (execve(full_path, args, environ) == -1)
			{
				perror("Execve");
				free(full_path);
				return (1);
			}
		}
		else
		{
			wait(&status);
		}
		free(full_path);
	}
	free(linea);
	free(args);
	return (0);
}
