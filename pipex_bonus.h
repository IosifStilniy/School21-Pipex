#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 30000
# endif

extern char	**environ;

int		maninp(char **argv);
int		file_check(int argc, char **argv, int m);
int		access_checker(char *path);
int		error_handler(int argn, char **argv, int funcres);
int		arrsize(char **argv);
int		eraser(void **p);
void	mounter(int leftpfd[2], int rightpfd[2], int infd, char **argv);

#endif