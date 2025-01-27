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
 * @mode: Input or output
 * Return: 0 in succes, -1 otherwise
 */
int	check_access(char *name, int mode)
{
	int	fd;

	if (name == NULL || *name == '\0')
	{
		write_error(mode, ft_strjoin("''", CMD_404));
		return (-1);
	}
	fd = open(name, O_DIRECTORY);
	if (fd != -1)
	{
		write_error(mode, ft_strjoin(name, IS_DIR));
		return (close(fd), -1);
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
void	write_error(int index, char *error_msg)
{
	int		fd;
	char	*error_log_name;
	char	*index_str;

	index_str = ft_itoa(index);
	error_log_name = ft_strjoin("error_log", index_str);
	fd = -1;
	fd = open(error_log_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		free(error_msg);
		free(index_str);
		free(error_log_name);
		return ;
	}
	ft_dprintf(fd, "%s", error_msg);
	free(error_msg);
	free(index_str);
	free(error_log_name);
	close(fd);
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
void	print_error(int n)
{
	int		i;
	char	*index;
	char	*file_name;

	i = 0;
	while (i < n)
	{
		index = ft_itoa(i);
		file_name = ft_strjoin("error_log", index);
		handle_error_components(file_name);
		free(index);
		free(file_name);
		i++;
	}
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
		unlink("here_doc.txt");
	while (wait(NULL) > 0)
		;
	free_2darray(strct->env);
	print_error(strct->ncmd);
}
