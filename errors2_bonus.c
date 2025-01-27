/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:58:19 by zzaoui            #+#    #+#             */
/*   Updated: 2025/01/27 20:07:58 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/**
 * check_pipe - Check the return value of a PIPE syscall
 * @pipe_return: The pipe return value
 * @strct: The main components structur
 */
void	check_pipe(int pipe_return, t_pipex strct)
{
	if (pipe_return == -1)
	{
		ft_dprintf(STDERR, "Pipe creation failed\n");
		free_2darray(strct.env);
		exit(-1);
	}
}

/**
 * fork_and_check - Forks and checks the return value of the fork
 * @strct: The main components structur
 * Return: The new process id
 */
pid_t	fork_and_check(t_pipex strct)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_dprintf(STDERR, "Fork creation failed\n");
		free_2darray(strct.env);
		exit(-1);
	}
	return (pid);
}
