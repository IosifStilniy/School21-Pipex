#include "pipex_bonus.h"

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

static int	grand_finale(int pidcount, pid_t *pids)
{
	int	i;
	int	stat_lock;

	i = 0;
	while (++i < pidcount)
		waitpid(pids[i], &stat_lock, WUNTRACED);
	return (WEXITSTATUS(stat_lock));
}

static int	forker(int argn, char **argv, int rightpfd[2], pid_t *pidsfd)
{
	int		leftpfd[2];

	leftpfd[0] = 0;
	leftpfd[1] = 0;
	if (argn == 1 || (!ft_strncmp("here_doc", argv[1], -1)))
		return (0);
	if (argn != 2 || (!ft_strncmp("here_doc", argv[1], -1)))
		error_handler(0, argv, pipe(leftpfd));
	forker(argn - 1, argv, leftpfd, pidsfd);
	if (leftpfd[1])
		error_handler(argn, argv, close(leftpfd[1]));
	pidsfd[argn - 1] = error_handler(0, argv, fork());
	if (pidsfd[argn - 1] > 0)
	{
		if (argn != 2 || !ft_strncmp("here_doc", argv[1], -1))
			error_handler(0, argv, close(leftpfd[0]));
		return (0);
	}
	mounter(leftpfd, rightpfd, pidsfd[0], argv);
	return (executor(argn, argv));
}

int	main(int argc, char **argv)
{
	int		fd[2];
	int		nullfd[2];
	pid_t	*pidsfd;

	if (argc < 4)
	{
		ft_putstr_fd(ft_strrchr(argv[0], '/') + 1, 1);
		ft_putstr_fd(": Too few arguments: need at least 3\n", 1);
		return (1);
	}
	nullfd[0] = 0;
	nullfd[1] = 0;
	if (!ft_strncmp(argv[1], "here_doc", -1) && !(argc < 5))
		fd[0] = maninp(argv);
	else if (!ft_strncmp(argv[1], "here_doc", -1))
		ft_putstr_fd(": Too few arguments: need at least 4\n", 1);
	else
		fd[0] = file_check(1, argv, R_OK);
	pidsfd = malloc(sizeof(*pidsfd) * (argc - 3 + 1));
	if (!pidsfd)
		error_handler(0, argv, -1);
	pidsfd[0] = fd[0];
	forker(argc - 2, argv, nullfd, pidsfd);
	return (grand_finale(argc - 2, pidsfd));
}
