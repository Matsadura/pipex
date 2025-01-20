#include "pipex.h"


int	main(int ac, char **av, char *envp[])
{
	pid_t id1, id2;
	int pipe_fd[2];
	char **arg;
	char **env;
	int	f;
	int	ret;

	(void)ac;
	env = parse_env(envp);
	if (pipe(pipe_fd) == -1)
	{
		perror("Pipe creation failed");
		exit(-1);
	}

	id1 = fork();
	if (id1 == 0)
	{
		f = open_file(av[1], env, STDIN_FILENO);
		dup_fd(pipe_fd, f, STDIN_FILENO);
		arg = ft_split(av[2], ' ');
		char *cmd = get_cmd(arg[0], env);
		if (cmd == NULL)
		{
			ft_putstr_fd("FIRST ARG\n", 2);
			free_2darray(arg);
			free_2darray(env);
			exit(127);
		}
		//perror(cmd);
		ret = execve(cmd, arg, env);
		if (ret == -1)
		{
			perror("First execve failed");
			free_2darray(arg);
			free(cmd);
			free_2darray(env);
			exit(126);
		}
	}

	id2 = fork();
	if (id2 == 0)
	{
		f = open_file(av[4], env, STDOUT_FILENO);
		//printf("child id1: %d\n", id1);
		dup_fd(pipe_fd, f, STDOUT_FILENO);

		arg = ft_split(av[3], ' ');
		char *cmd = get_cmd(arg[0], env);
		if (cmd == NULL)
		{
		//	waitpid(id1, NULL, 0);
			ft_putstr_fd("SECOND ARG\n", 2);
			free_2darray(arg);
			free_2darray(env);
			exit(127);
		}
		ret = execve(cmd, arg, env);
		if (ret == -1)
		{
			perror("Second execve failed");
			free_2darray(arg);
			free(cmd);
			free_2darray(env);
			exit(126);
		}
	}

	//printf("parent id1: %d\n", id1);
	free_2darray(env);
	close_pipe(pipe_fd);
	waitpid(id1, NULL, 0);
	waitpid(id2, NULL, 0);
	return (0);
}