#include "main.h"

char *_getenv(const char *name)
{
        extern char **environ;
        int i = 0;
        char *token, *copy_env, *value;

        while (environ[i])
        {
		copy_env = strdup(environ[i]);
		token = strtok(copy_env, "=");

                if (strcmp(token, name) == 0)
                {
			value = strdup(strtok(NULL, "="));
            		free(copy_env);
            		return value;
                }
		free(copy_env);
                i++;
        }
        return NULL;
}

char *check_command(char *command, char *path)
{
    char *full_path = malloc(1024);
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
            return strdup(command);
        }
        free(copy_path);
        free(full_path);
        return NULL;
    }

    token = strtok(copy_path, ":");
    while (token != NULL)
    {
        sprintf(full_path, "%s/%s", token, command);
        if (stat(full_path, &st) == 0)
        {
            free(copy_path);
            return strdup(full_path);
        }
        token = strtok(NULL, ":");
    }

    free(copy_path);
    free(full_path);
    return NULL;
}

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
void limpiar(char **linea, char ***args, char **full_path)
{
        if (*linea)
	{
                free(*linea);
		*linea = NULL;
	}
        if (*args)
	{
		free(*args);
		*args = NULL;
	}
        if (*full_path)
	{
                free(*full_path);
		*full_path = NULL;
	}
}
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
