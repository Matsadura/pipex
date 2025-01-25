/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:48:59 by zzaoui            #+#    #+#             */
/*   Updated: 2025/01/22 21:50:17 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * check_access - Checks the command access
 * @name: The command name
 * @mode: Input or output
 * Return: 0 in succes, -1 otherwise
 */
int	check_access(char *name, int mode)
{
	if (name == NULL || *name == '\0')
	{
		write_error(mode, ft_strjoin("''", CMD_404));
		return (-1);
	}
	if (open(name, O_DIRECTORY) != -1)
	{
		write_error(mode, ft_strjoin(name, IS_DIR));
		return (-1);
	}
	if (access(name, F_OK) != 0)
	{
		write_error(mode, ft_strjoin(name, CMD_404));
		return (-1);
	}
	else if (access(name, X_OK) != 0)
	{
		write_error(mode, ft_strjoin(name, CMD_403));
		return (-1);
	}
	return (0);
}

/**
 * write_error - Write the error message in it's corresponding log file
 * @mode: Input our output
 * @error_msg: The error message to write
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
	ft_dprintf(fd, "%s", error_msg);
	free(error_msg);
}

/**
 * handle_error_components - Reads the error in temporary log file, prints it,
 *		and unlinks it.
 * @file_name: The log file name
 */
void	handle_error_components(char *file_name)
{
	char	buff[4096];
	int		fd;
	ssize_t	bytes;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return ;
	unlink(file_name);
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buff, sizeof(buff) - 1);
		buff[bytes] = '\0';
		ft_dprintf(2, "%s", buff);
	}
	close(fd);
}

/**
 * print_error - Wrapper around handle_error_components
 */
void	print_error(void)
{
	handle_error_components("cmd0_error.log");
	handle_error_components("cmd1_error.log");
}

/**
 * cleanup - Wrapper around cleaning operations
 * @strct: main components structure
 * @id1: first child process id
 * @id2: second child process id
 * @status: second child exit status
 */
void	cleanup(t_pipex strct, pid_t id1, pid_t id2, int *status)
{
	free_2darray(strct.env);
	close_pipe(strct.pipe_fd);
	waitpid(id1, NULL, 0);
	waitpid(id2, status, 0);
	print_error();
}
