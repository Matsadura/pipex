/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:48:59 by zzaoui            #+#    #+#             */
/*   Updated: 2025/01/20 17:49:01 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * 
 */
int	check_access(char *name, int mode)
{
	if (name == NULL)
		return (-1);
	if (access(name, F_OK) != 0)
	{
		write_error(mode, ft_strjoin(name, ": command not found\n"));
		return (-1);
	}
	else if (access(name, X_OK) != 0)
	{
		write_error(mode, ft_strjoin(name ,": permission denied\n"));
		return (-1);
	}
	return (0);
}

/**
 * 
 */
void	write_error(int mode, char *error_msg)
{
	int	fd;

	fd = -1;
	if (mode == 0)
		fd = open("cmd0_error.log", O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (mode == 1)
		fd = open("cmd1_error.log", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		free(error_msg);
		return ;
	}
	ft_putstr_fd(error_msg, fd);
	free(error_msg);
}


/**
 * read_error_buffer
 */
void	read_error_buffer(char *file_name)
{
	int fd;
	ssize_t	bytes;
	char	buff[4096];

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return;
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buff, sizeof(buff) - 1);
		buff[bytes] = '\0';
		ft_putstr_fd(buff, 2);
	}
	close(fd);
	unlink(file_name);
}

/**
 * print_error
 */
void	print_error(void)
{
	read_error_buffer("cmd0_error.log");
	read_error_buffer("cmd1_error.log");
}