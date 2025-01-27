/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_remake.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:21:38 by zzaoui            #+#    #+#             */
/*   Updated: 2025/01/27 20:27:38 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/**
 * main - Pipex program entry point
 * @ac: The number of command line arguments
 * @av: Argument vector
 * @envp: Pointer to an array of enviromental variables
 */
int	main(int ac, char **av, char *envp[])
{
	int		i;
	pid_t	pid;
	t_pipex	strct;

	if (ac < 5)
	{
		ft_printf("Usage: ./pipex in cmd1 ... cmd2 out\n");
		return (EXIT_FAILURE);
	}
	t_init(&strct, envp, ac, av);
	i = 0;
	handle_heredoc(&strct);
	while (i < strct.ncmd)
	{
		if (i < strct.ncmd - 1)
			check_pipe(pipe(strct.pipe_fd), strct);
		pid = fork_and_check(strct);
		if (pid == 0)
			handle_child(strct, i);
		else
			handle_parent(&strct, i);
		i++;
	}
	cleanup(&strct, pid);
	return (WEXITSTATUS(strct.status));
}
