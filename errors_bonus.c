/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:48:59 by zzaoui            #+#    #+#             */
/*   Updated: 2025/01/27 20:23:20 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	ft_putstr_fd(err, STDERR);
	free(err);
}

/**
 * cleanup - Wrapper around cleaning operations
 * @strct: pointer to main components structure
 * @pid: last command process id
 */
void	cleanup(t_pipex *strct, pid_t pid)
{
	waitpid(pid, &strct->status, 0);
	if (strct->is_hdoc == TRUE)
	{
		unlink(strct->infile);
		free(strct->infile);
	}
	while (wait(NULL) > 0)
		;
	free_2darray(strct->env);
}
