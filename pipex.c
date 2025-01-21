/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:21:38 by zzaoui            #+#    #+#             */
/*   Updated: 2025/01/21 17:24:29 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char *envp[])
{
	char	**env;
	pid_t	id1;
	pid_t	id2;
	int		pipe_fd[2];

	(void)ac;
	env = parse_env(envp);
	if (pipe(pipe_fd) == -1)
		exit(-1);
	id1 = fork();
	if (id1 == -1)
		exit(-1);
	if (id1 == 0)
		handle_child(env, av, pipe_fd, STDIN_FILENO);
	id2 = fork();
	if (id2 == -1)
		exit(-1);
	if (id2 == 0)
		handle_child(env, av, pipe_fd, STDOUT_FILENO);
	free_2darray(env);
	close_pipe(pipe_fd);
	waitpid(id1, NULL, 0);
	waitpid(id2, NULL, 0);
	print_error();
	return (0);
}
