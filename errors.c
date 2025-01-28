/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:48:59 by zzaoui            #+#    #+#             */
/*   Updated: 2025/01/28 16:29:57 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * check_access - Checks the command access
 * @name: The command name
 * Return: 0 in succes, -1 otherwise
 */
int	check_access(char *name)
{
	int		fd;
	char	*err;

	if (name == NULL || *name == '\0')
	{
		err = ft_strjoin("''", CMD_404);
		return (put_and_free(err), -1);
	}
	fd = open(name, O_DIRECTORY);
	if (fd != -1)
	{
		err = ft_strjoin(name, IS_DIR);
		return (close(fd), put_and_free(err), -1);
	}
	if (access(name, F_OK) != 0)
	{
		err = ft_strjoin(name, CMD_404);
		return (put_and_free(err), -1);
	}
	else if (access(name, X_OK) != 0)
	{
		err = ft_strjoin(name, CMD_403);
		return (put_and_free(err), -1);
	}
	return (0);
}

/**
 * put_and_free - Prints to STDERR and frees the error message
 */
void	put_and_free(char *err)
{
	ft_putstr_fd(err, 2);
	free(err);
}

/**
 * cleanup - Wrapper around cleaning operations
 * @strct: pointer to main components structure
 * @id1: first child process id
 * @id2: second child process id
 */
void	cleanup(t_pipex *strct, pid_t id1, pid_t id2)
{
	free_2darray(strct->env);
	close_pipe(strct->pipe_fd);
	waitpid(id1, NULL, 0);
	waitpid(id2, &strct->status, 0);
}
