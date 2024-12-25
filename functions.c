#include "main.h"

char *_getenv(const char *name)
{
        extern char **environ;
        int i = 0;
        char *token;

        while (environ[i])
        {
                token = strtok(environ[i], "=");

                if (strcmp(token, name) == 0)
                {
                        return (strtok(NULL, "="));
                }
                i++;
        }
        return (NULL);
}

char *check_command (char *command, char *path)
{
	char *copy_path = strdup(path);
	char *token;
	char *full_path = malloc(sizeof(char *) * 1024);
	struct stat st;

	token = strtok(copy_path, ":");

	while (token != NULL)
	{
		sprintf(full_path, "%s/%s", token, command);

		if (stat(full_path, &st) == 0)
		{
			free(copy_path);
			return (full_path);
		}
		token = strtok(NULL, ":");
	}
	free(copy_path);
	free(full_path);
	return (NULL);
}
