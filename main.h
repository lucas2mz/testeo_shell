#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <sys/stat.h>
extern char **environ;
void print(void);
void print2(void);
char *_getenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
char *check_command(char *command, char *path);
char **tokenizar(char *linea, char *delim);
void limpiar(char *linea, char **args, char *full_path);
int leer_linea(char **linea);
int ejecutar_comando(char *full_path, char **args);
#endif
