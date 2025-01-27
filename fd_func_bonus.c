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

#include "pipex_bonus.h"

void dup_and_close(int fd1, int fd2, int mode)
{
	close(fd1);
	dup2(fd2, mode);
	close(fd2);
}

void dup_and_close_file(int fd, int mode)
{
	dup2(fd, mode);
	close(fd);
}

int open_input_file(t_pipex strct)
{
	int fd;

	fd = open(strct.infile, O_RDONLY);
	if (fd < 0)
	{
		perror(strct.infile);
		/*Free env here*/
		exit(-1);
	}
	return (fd);
}

int open_output_file(t_pipex strct)
{
	int fd;

	fd = open(strct.outfile, strct.out_perms, 0644);
	if (fd < 0)
	{
		perror(strct.outfile);
		/*Free env here*/
		exit(-1);
	}
	return (fd);
}
