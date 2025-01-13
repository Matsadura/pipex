#include "pipex.h"


int	main(int ac, char **av, char *envp[])
{
	pid_t id1, id2;
	int fd[2];
	char **arg;
	char *env[] = {"/usr/bin", NULL};
	int	f;
	int	ret;

	(void)ac;
	(void)envp;
	if (pipe(fd) == -1)
	{
		perror("Pipe creation failed");
		exit(1);
	}

	id1 = fork();
	if (id1 == 0)
	{
		close(fd[0]);
		if (access(av[1], F_OK | R_OK) != 0)
		{
			perror("IN file access failed");
			exit(2);
		}
		f = open(av[1], O_RDONLY, 0644);
		dup2(f, 0);
		close(f);
		dup2(fd[1], 1);
		close(fd[1]);

		arg = ft_split(av[2], ' ');
		ret = execve(arg[0], arg, env);
		if (ret == -1)
		{
			perror("First execve failed");
			exit(3);
		}
	}

	id2 = fork();
	if (id2 == 0)
	{
		close(fd[1]);
		f = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (access(av[4], F_OK | W_OK) != 0)
		{
			perror("OUT file access failed");
			exit(5);
		}
		dup2(f, 1);
		close(f);
		dup2(fd[0], 0);
		close(fd[0]);
		arg = ft_split(av[3], ' ');
		ret = execve(arg[0], arg, env);
		if (ret == -1)
		{
			perror("Second execve failed");
			exit(4);
		}
	}

	close(fd[0]);
	close(fd[1]);
	waitpid(id1, NULL, 0);
	waitpid(id2, NULL, 0);
	return (0);
}
