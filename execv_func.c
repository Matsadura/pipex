/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execv_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:09:08 by zzaoui            #+#    #+#             */
/*   Updated: 2025/01/21 17:09:19 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

/**
 * 
 */
void    handle_child(char **env, char **av, int pipe_fd[], int mode)
{
    int     f;
    char    *cmd;
    char    **arg;

	f = open_file(av[1], env, mode);
	dup_fd(pipe_fd, f, mode);
	arg = ft_split(av[mode + 2], ' ');
	cmd = get_cmd(arg[0], env);
	if (cmd == NULL)
	{
	 	if (check_access(arg[0], mode) == -1)
		{
			free_2darray(arg);
			free_2darray(env);
			exit(127);
		}
	}
	if (execve(cmd, arg, env) == - 1)
	{
		free_2darray(arg);
		free(cmd);
		free_2darray(env);
		exit(126);
	}
}