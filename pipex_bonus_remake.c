/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:21:38 by zzaoui            #+#    #+#             */
/*   Updated: 2025/01/22 16:19:36 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

#define READ_END 0
#define WRITE_END 1
#define STDIN 0
#define STDOUT 1
#define STDERR 2

void check_pipe(int pipe_return)
{
	if (pipe_return == -1)
	{
		ft_dprintf(STDERR, "Pipe creation failed\n");
		/* Free Env Here */
		exit(-1);
	}
}

pid_t fork_and_check(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_dprintf(STDERR, "Fork creation failed\n");
		/* Free Env Here */
		exit(-1);
	}
	return (pid);
}

void dup_and_close(int fd1, int fd2, int mode)
{
	close(fd1);
	dup2(fd2, mode);
	close(fd2);
}

void dup_and_close_file(int fd, int mode)
{
	dup2(fd, mode);
	close(fd);
}

int open_input_file(char *file_name)
{
	int fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		perror(file_name);
		/*Free env here*/
		exit(-1);
	}
	return (fd);
}

int open_output_file(char *file_name)
{
	int fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(file_name);
		/*Free env here*/
		exit(-1);
	}
	return (fd);
}

void execute_cmd(char *arg, char **env, int index)
{
	char **args;
	char *cmd;

	args = ft_split(arg, ' ');
	cmd = get_cmd(args[0], env);
	//ft_dprintf(2, "CMD IS: %s\n", cmd);
	if (cmd == NULL)
	{
		if (check_access(args[0], index) == -1)
		{
			//ft_dprintf(STDERR, "CMD: %s Failed\n", args[0]);
			/*Free allocated memory (args / env)*/
			free_2darray(args);
			free_2darray(env);
			exit(127);
		}
	}
	if (execve(cmd, args, env) == -1)
	{
		perror(cmd);
		/*Free allocated memory (args / cmd / env)*/
		free_2darray(args);
		free_2darray(env);
		free(cmd);
		exit(126);
	}
}

int	main(int ac, char **av, char *envp[])
{
	int	i;
	int	in_fd;
	int	out_fd;
	int	old_pipe;
	int stat;
	int	pipe_fd[2];
	pid_t	pid;
	char **env;

	if (ac < 5)
	{
		ft_printf("Usage: ./pipex in cmd1 ... cmd2 out\n");
		return (EXIT_FAILURE);
	}
	env = parse_env(envp);
	i = 0;
	old_pipe = -1;
	while(i < ac - 3)
	{
		if (i < ac - 4)
			check_pipe(pipe(pipe_fd));
		pid = fork_and_check();
		if (pid == 0)
		{
			if (i == 0)
			{
				if (i < ac - 4)
					dup_and_close(pipe_fd[READ_END], pipe_fd[WRITE_END], STDOUT);
				in_fd = open_input_file(av[1]);
				dup_and_close_file(in_fd, STDIN);			
			}
			else
			{
				dup_and_close_file(old_pipe, STDIN);
				if (i == ac - 4)
				{
					out_fd = open_output_file(av[ac - 1]);
					dup_and_close_file(out_fd, STDOUT);			
				}
				else
					dup_and_close(pipe_fd[READ_END], pipe_fd[WRITE_END], STDOUT);
			}
			execute_cmd(av[i + 2], env, i);
		}
		else
		{
			if (old_pipe != -1)
				close(old_pipe);
			if (i < ac - 4)
			{
				old_pipe = pipe_fd[READ_END];
				close(pipe_fd[WRITE_END]);
			}
			else
				old_pipe = -1;
		}
		i++;
	}
	while (wait(&stat) > 0);
	free_2darray(env);
	print_error(ac - 3);
	return (WEXITSTATUS(stat));
}
