#include "main.h"

int main(int ac, char **av)
{
	char *linea = NULL, *token = NULL, *args[100];
	size_t size = 0;
	ssize_t len = 0;
	int i, status = 0;
	pid_t hijo1;

	print2();

	while (1)
	{
		printf("#Shellzilla$ ");
		len = getline(&linea, &size, stdin);

		if (len == -1)
		{
			break;
		}

		i = 0;

		token = strtok(linea, " \t\n");

		while (token != NULL)
		{
			args[i] = token;
			token = strtok(NULL, " \t\n");
			i++;
		}
		args[i] = NULL;

		if (args[0] != NULL && strcmp(args[0], "exit") == 0)
		{
			break;
		}

		if (args[0] == NULL)
		{
			continue;
		}

		hijo1 = fork();
		if (hijo1 == -1)
		{
			exit(-1);
		}
		if (hijo1 == 0)
		{	
			if (execve(args[0], args, NULL) == -1)
			{
				printf("Shellzilla: No such file or directory\n");
				exit(1);
			}
		}
/
		else if (hijo1 > 0)
		{
			wait(&status);
		}
	}
	free(linea);

	return (0);
}
