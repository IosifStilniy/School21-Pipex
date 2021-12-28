#include "pipex_bonus.h"

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
	if (mod == W_OK && ft_strncmp(argv[1], "here_doc", -1)
		&& ((fd > 0 && !close(fd)) || fd))
		fd = open(argv[argn], O_WRONLY | O_TRUNC | O_APPEND);
	else if (mod == W_OK && ((fd > 0 && !close(fd)) || fd))
		fd = open(argv[argn], O_WRONLY | O_APPEND);
	else if (!fd)
		fd = open(argv[argn], O_WRONLY | O_CREAT | O_EXCL | O_APPEND, 420);
	if (!fd || fd == -1)
		error_handler(argn, argv, -1);
	return (fd);
}

int	access_checker(char *path)
{
	if (!access(path, F_OK))
	{
		if (!access(path, X_OK))
			return (0);
		return (-2);
	}
	return (-1);
}

int	maninp(char **argv)
{
	int		pfd[2];
	char	buf[BUFFER_SIZE + 1];
	int		ret;

	while (pipe(pfd))
		;
	ret = 1;
	ft_putstr_fd("here_doc> ", 1);
	while (1)
	{
		if (ret && ft_strrchr(buf, '\n'))
			ft_putstr_fd("here_doc> ", 1);
		ret = error_handler(0, argv, read(0, buf, BUFFER_SIZE));
		buf[ret] = '\0';
		if (ret - 1 == (int)ft_strlen(argv[2]) && ft_strnstr(buf, argv[2], -1))
		{
			error_handler(0, argv, close(pfd[1]));
			ret = error_handler(0, argv, dup(pfd[0]));
			error_handler(0, argv, close(pfd[0]));
			return (ret);
		}
		ft_putstr_fd(buf, pfd[1]);
	}
	return (error_handler(0, argv, -1));
}
