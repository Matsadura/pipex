/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:39:12 by zzaoui            #+#    #+#             */
/*   Updated: 2025/01/23 16:26:12 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * open_file - Open a file for reading or writing
 * @file_name: The file to open
 * @env: The env path
 * @mode: STDIN or STDOUT
 * Return: the new file descriptor
 */
int	open_file(char *file_name, t_pipex strct, char mode)
{
	int	fd;

	fd = -1;
	if (mode == STDIN_FILENO)
		fd = open(file_name, O_RDONLY);
	else if (mode == STDOUT_FILENO)
		fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(file_name);
		free_2darray(strct.env);
		exit(13);
	}
	return (fd);
}

/**
 * dup_fd - Duplicates file descriptors
 * @file_fd: open file descriptor
 * @pipe_fd: pipe line file descriptors
 */
void	dup_fd(t_pipex strct, char *file_name, int mode)
{
	int	file_fd;

	file_fd = -1;
	if (mode == 0)
	{
		close(strct.pipe_fd[0]);
		dup2(strct.pipe_fd[1], 1);
		close(strct.pipe_fd[1]);
		file_fd = open_file(file_name, strct, mode);
		dup2(file_fd, 0);
		close(file_fd);
	}
	else if (mode == 1)
	{
		close(strct.pipe_fd[1]);
		dup2(strct.pipe_fd[0], 0);
		close(strct.pipe_fd[0]);
		file_fd = open_file(file_name, strct, mode);
		dup2(file_fd, 1);
		close(file_fd);
	}
}

/**
 * close_pipe - Closes the pipe file descriptors
 * @pipe_fd: The pipe's file descriptors
 */
void	close_pipe(int pipe_fd[])
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}
