#include "pipex.h"

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

	if (leftpfd[0] == 0)
		leftpfd[0] = infd;
	if (!rightpfd[1])
	{
		i = 0;
		while (argv[i])
			i++;
		rightpfd[1] = file_check(--i, argv, W_OK);
	}
	dup2(leftpfd[0], 0);
	dup2(rightpfd[1], 1);
	close(leftpfd[0]);
	close(rightpfd[1]);
}

int	arrsize(char **argv)
{
	int	size;

	size = 0;
	while (argv[size])
		size++;
	return (size);
}

int	file_check(int argn, char **argv, int mod)
{
	int	fd;

	fd = 0;
	if (!access(argv[argn], F_OK) && !access(argv[argn], mod))
		fd = open(argv[argn], O_RDWR);
	if ((mod == R_OK && !fd) || (fd == -1 && errno == 21))
		error_handler(argn, argv, -1);
	if (mod == R_OK && ((fd > 0 && !close(fd)) || fd))
		fd = error_handler(argn, argv, open(argv[argn], O_RDONLY));
	if (mod == W_OK && ((fd > 0 && !close(fd)) || fd))
		fd = open(argv[argn], O_WRONLY | O_TRUNC | O_APPEND);
	else if (!fd)
		fd = open(argv[argn], O_WRONLY | O_CREAT | O_EXCL | O_APPEND, 420);
	if (!fd || fd == -1)
		error_handler(argn, argv, -1);
	return (fd);
}
