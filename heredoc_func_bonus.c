/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_func_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:27:42 by zzaoui            #+#    #+#             */
/*   Updated: 2025/01/30 14:27:33 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/**
 *
 */
static char	*random_name(void)
{
	long	n;
	char	*name;
	char	*full_name;

	n = 1;
	name = ft_ltoa((long) &n);
	while (1)
	{
		if (access(name, F_OK) == -1)
			break ;
		free(name);
		n++;
		name = ft_ltoa((long) &n);
	}
	full_name = ft_strjoin("/tmp/", name);
	free(name);
	return (full_name);
}

/**
 * handle_heredoc - Checks if a heredoc is present and updates
 *	the structure members accordignly
 * @strct: The main components structure
 */
void	handle_heredoc(t_pipex *strct)
{
	if (ft_strncmp("here_doc", strct->av[1], ft_strlen("here_doc") + 1) == 0)
	{
		strct->infile = random_name();
		strct->out_perms = O_CREAT | O_WRONLY | O_APPEND;
		strct->ncmd -= 1;
		strct->delim = strct->av[2];
		strct->is_hdoc = TRUE;
		write_in_heredoc(*strct);
	}
}

/**
 * write_in_heredoc - Writes STDIN in a tmp file
 * @strct: The main components structure
 */
void	write_in_heredoc(t_pipex strct)
{
	char	*line;
	char	*delim;
	int		fd;

	fd = open(strct.infile, O_CREAT | O_WRONLY, 0644);
	if (fd < 0)
		return ;
	delim = ft_strjoin(strct.delim, "\n");
	if (delim == NULL)
		close(fd);
	ft_dprintf(0, "> ");
	line = get_next_line(0);
	while (line != NULL)
	{
		if (ft_strncmp(line, delim, ft_strlen(delim)) == 0)
		{
			free(line);
			break ;
		}
		put_and_print(line, fd);
		free(line);
		line = get_next_line(0);
	}
	free(delim);
	close(fd);
}

/**
 * put_and_print - Writes the line in the FD and prints >
 * @line: Pointer to the line variable
 * @fd: File descriptor of the file to write in
 */
void	put_and_print(char *line, int fd)
{
	ft_putstr_fd(line, fd);
	ft_dprintf(0, "> ");
}
