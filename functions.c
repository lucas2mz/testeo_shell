#include "main.h"
/*
 * _getenv - Gets the environment
 * @name: The directory to check
 *
 * Return: The directory or NULL if is fail
 */
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
	return NULL;
}
/*
 * chech_command - Checks if the command exist
 * @command: Command to be checked
 * @path: The path to go over
 *
 * Return: NULL if it fail or command in success
 */
char *check_command(char *command, char *path)
{
	char *full_path = malloc(sizeof(char) * 1024);
	char *copy_path = strdup(path);
	struct stat st;
	char *token;

	if (!full_path || !copy_path)
	{
		free(full_path);
		free(copy_path);
		return NULL;
	}

	if (command[0] == '/')
	{
		if (access(command, X_OK) == 0)
		{
			free(copy_path);
			free(full_path);
			return (strdup(command));
		}
		free(copy_path);
		free(full_path);
		return (NULL);
	}

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
/*
 * tokenizar - Crates tokens
 *
 * @linea: Line to token
 * @delim: The delimiters
 *
 * Return: Always args
 */
char **tokenizar(char *linea, char *delim)
{
	char **args = malloc(sizeof(char *) * 1024);
	char *token;
	int i = 0;

	token = strtok(linea, delim);

	while (token != NULL)
	{
		args[i] = token;
		token = strtok(NULL, delim);
		i++;
	}
	args[i] = NULL;

	return (args);
}
/*
 * limpiar - Free dynamic memory
 * 
 * @linea: Line to free
 * @args: Args to be freed
 * @full_path: Path to free
 */
void limpiar(char *linea, char **args, char *full_path)
{
	if (linea)
		free(linea);
	if (args)
	{
		free(args);
	}
	if (full_path)
		free(full_path);
}
/*
 * leer_linea - Read the output of the user
 * @linea: Line to read
 *
 * Return: 0 to break or 1 in success
 */
int leer_linea(char **linea)
{
	size_t size = 0;
	ssize_t len = 0;

	len = getline(linea, &size, stdin);

	if (len == -1)
	{
		return (0);
	}
	if (strcmp(*linea, "exit\n") == 0)
	{
		return (0);
	}

	return (1);
}
