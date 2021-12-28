#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <stdio.h>

extern char	**environ;

int		file_check(int argc, char **argv, int m);
int		error_handler(int argn, char **argv, int funcres);
int		arrsize(char **argv);
int		eraser(void **p);
void	mounter(int leftpfd[2], int rightpfd[2], int infd, char **argv);

#endif