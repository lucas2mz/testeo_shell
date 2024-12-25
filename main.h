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
char *check_command (char *command, char *path);
#endif
