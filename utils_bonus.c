#include "pipex_bonus.h"

int	error_handler(int argn, char **argv, int funcres)
{
	if (funcres >= 0)
		return (funcres);
	ft_putstr_fd(ft_strrchr(argv[0], '/') + 1, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	if (!argn)
	{
		ft_putchar_fd('\n', 2);
		exit(1);
	}
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(argv[argn], 2);
	ft_putchar_fd('\n', 2);
	exit(1);
}

int	eraser(void **p)
{
	size_t	i;

	i = arrsize((char **)p);
	while (p[i])
		free(p[i--]);
	free(p);
	return (1);
}

void	mounter(int leftpfd[2], int rightpfd[2], int infd, char **argv)
{
	int	i;

	if (!leftpfd[0])
		leftpfd[0] = infd;
	i = 0;
	if (!rightpfd[1])
	{
		while (argv[i])
			i++;
		rightpfd[1] = file_check(--i, argv, W_OK);
	}
	dup2(leftpfd[0], 0);
	dup2(rightpfd[1], 1);
	close(leftpfd[0]);
	close(rightpfd[1]);
	if (rightpfd[0])
		close(rightpfd[0]);
}

int	arrsize(char **argv)
{
	int	size;

	size = 0;
	while (argv[size])
		size++;
	return (size);
}
