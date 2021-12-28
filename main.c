#include "pipex.h"

static int	access_checker(char *path)
{
	if (!access(path, F_OK))
	{
		if (!access(path, X_OK))
			return (0);
		return (-2);
	}
	return (-1);
}

static char	*pathdefiner(char *prog)
{
	char	**path;
	char	*bpath;
	int		acs;
	int		i;

	i = -1;
	while (environ[++i])
		if (ft_strnstr(environ[i], "PATH=", ft_strlen("PATH=")))
			break ;
	if (i == arrsize(environ))
		return (NULL);
	path = ft_split(environ[i] + ft_strlen("PATH="), ':');
	i = arrsize(path);
	while (--i - 1)
	{
		bpath = ft_strjoin(path[i - 1], prog);
		acs = access_checker(bpath);
		if (!acs && eraser((void **)path))
			return (bpath);
		free(bpath);
		if (acs == -2 && eraser((void **)path))
			return (NULL);
	}
	eraser((void **)path);
	return (NULL);
}

static int	executor(int argn, char **argv)
{
	char	**flags;
	char	*buf;
	char	*path;

	flags = ft_split(argv[argn], ' ');
	if (flags && ft_strchr(flags[0], '/'))
	{
		path = flags[0];
		flags[0] = ft_strrchr(flags[0], '/') + 1;
		return (error_handler(argn, argv, execve(path, flags, environ)));
	}
	else if (!flags)
		return (error_handler(argn, argv, -1));
	buf = ft_strjoin("/", flags[0]);
	path = pathdefiner(buf);
	if (!path)
		return (error_handler(argn, argv, -1));
	else
		return (error_handler(argn, argv, execve(path, flags, environ)));
	exit(1);
}

static int	forker(int argn, char **argv, int rightpfd[2], int infd)
{
	int		leftpfd[2];
	int		stat_loc;
	pid_t	pid;

	leftpfd[0] = 0;
	leftpfd[1] = 0;
	if (argn == 1)
		return (0);
	if (argn != 2)
		error_handler(0, argv, pipe(leftpfd));
	forker(argn - 1, argv, leftpfd, infd);
	if (argn != 2)
		error_handler(argn, argv, close(leftpfd[1]));
	pid = error_handler(0, argv, fork());
	if (pid > 0)
	{
		error_handler(argn, argv, waitpid(-1, &stat_loc, WUNTRACED));
		if (argn != 2)
			error_handler(argn, argv, close(leftpfd[0]));
		return (WEXITSTATUS(stat_loc));
	}
	mounter(leftpfd, rightpfd, infd, argv);
	return (executor(argn, argv));
}

int	main(int argc, char **argv)
{
	int	fd;
	int	nullfd[2];

	if (argc != 5)
	{
		ft_putstr_fd(ft_strrchr(argv[0], '/') + 1, 1);
		ft_putstr_fd(": Stricly 4 args: input_file cmd1 cmd2 output_file\n", 1);
		return (1);
	}
	nullfd[0] = 0;
	nullfd[1] = 0;
	fd = file_check(1, argv, R_OK);
	return (forker(argc - 2, argv, nullfd, fd));
}
