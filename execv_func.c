/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execv_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:09:08 by zzaoui            #+#    #+#             */
/*   Updated: 2025/01/23 23:44:36 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * handle_child - Wrapper around child fork logic
 * @strct: Structure contains Pipe_fd, env, and args
 * @index: File index
 */
void	handle_child(t_pipex strct, int mode, int index)
{
	char	*cmd;
	char	**arg;

	dup_fd(strct, strct.av[index], mode);
	arg = ft_split(strct.av[mode + 2], ' ');
	cmd = get_cmd(arg[0], strct.env);
	if (cmd == NULL)
	{
		if (check_access(arg[0], mode) == -1)
		{
			free_2darray(arg);
			free_2darray(strct.env);
			exit(127);
		}
	}
	if (execve(cmd, arg, strct.env) == -1)
	{
		perror(cmd);
		free_2darray(arg);
		free(cmd);
		free_2darray(strct.env);
		exit(126);
	}
}
