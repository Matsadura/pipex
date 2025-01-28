/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_func_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 10:31:59 by zzaoui            #+#    #+#             */
/*   Updated: 2025/01/28 12:36:43 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/**
 * dup_and_close - Duplicates an FD and closes
 * @fd1: The FD to close
 * @fd2: The FD to duplicate and close
 * @mode: STDIN or STDOUT
 */
void	dup_and_close(int fd1, int fd2, int mode)
{
	close(fd1);
	dup2(fd2, mode);
	close(fd2);
}

/**
 * dup_and_close_file - Duplicates an FD and closes
 * @fd2: The FD to duplicate and close
 * @mode: STDIN or STDOUT
 */
void	dup_and_close_file(int fd, int mode)
{
	dup2(fd, mode);
	close(fd);
}

/**
 * open_input_file - Opens a file
 * @strct: The main componenets structure
 * Return: The new file descriptor
 */
int	open_input_file(t_pipex strct)
{
	int	fd;

	fd = open(strct.infile, O_RDONLY);
	if (fd < 0)
	{
		perror(strct.infile);
		free_2darray(strct.env);
		exit(1);
	}
	return (fd);
}

/**
 * open_output_file - Opens a file
 * @strct: The main componenets structure
 * Return: The new file descriptor
 */
int	open_output_file(t_pipex strct)
{
	int	fd;

	fd = open(strct.outfile, strct.out_perms, 0644);
	if (fd < 0)
	{
		perror(strct.outfile);
		free_2darray(strct.env);
		exit(1);
	}
	return (fd);
}
