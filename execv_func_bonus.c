/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execv_func_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:09:08 by zzaoui            #+#    #+#             */
/*   Updated: 2025/01/27 20:42:41 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/**
 * 
 */
static void	check_and_free(t_pipex strct, char **args, char **env)
{
	if (strct.is_hdoc == TRUE)
		free(strct.infile);
	free_2darray(args);
	free_2darray(env);
}

/**
 * execute_cmd - Executes a command
 * @arg: The command with it's arguments
 * @env: The path variable
 * @index: The command index
 */
void	execute_cmd(char *arg, char **env, t_pipex strct)
{
	char	**args;
	char	*cmd;

	args = ft_split(arg, ' ');
	cmd = get_cmd(args[0], env);
	if (cmd == NULL)
	{
		if (check_access(args[0]) == -1)
		{
			check_and_free(strct, args, env);
			exit(127);
		}
	}
	if (execve(cmd, args, env) == -1)
	{
		perror(cmd);
		check_and_free(strct, args, env);
		free(cmd);
		exit(126);
	}
}

/**
 * handle_child - Wrapper around children pipe logic
 * @strct: Structure contains Pipe_fd, env, args and more
 * @idx: command index
 */
void	handle_child(t_pipex strct, int idx)
{
	if (idx == 0)
	{
		if (idx < strct.ncmd - 1)
			dup_and_close(strct.pipe_fd[READ_END], \
					strct.pipe_fd[WRITE_END], STDOUT);
		strct.in_fd = open_input_file(strct);
		dup_and_close_file(strct.in_fd, STDIN);
	}
	else
	{
		dup_and_close_file(strct.old_pipe, STDIN);
		if (idx == strct.ncmd - 1)
		{
			strct.out_fd = open_output_file(strct);
			dup_and_close_file(strct.out_fd, STDOUT);
		}
		else
			dup_and_close(strct.pipe_fd[READ_END], \
					strct.pipe_fd[WRITE_END], STDOUT);
	}
	if (strct.is_hdoc == TRUE)
		execute_cmd(strct.av[idx + 3], strct.env, strct);
	else
		execute_cmd(strct.av[idx + 2], strct.env, strct);
}

/**
 * handle_parent - Wrapper around parent pipe logic
 * @strct: Structure contains Pipe_fd, env, args and more
 * @idx: command index
 */
void	handle_parent(t_pipex *strct, int idx)
{
	if (strct->old_pipe != -1)
		close(strct->old_pipe);
	if (idx < strct->ncmd - 1)
	{
		strct->old_pipe = strct->pipe_fd[READ_END];
		close(strct->pipe_fd[WRITE_END]);
	}
	else
		strct->old_pipe = -1;
}
