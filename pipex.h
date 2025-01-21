/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:39:28 by zzaoui            #+#    #+#             */
/*   Updated: 2025/01/20 17:37:09 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <sys/wait.h>
# include <errno.h>
# include <string.h>

typedef struct s_pipex
{
    char    **env;
    char    **av;
    int     pipe_fd[2];    
} t_pipex;

/** 2D Array functions **/
void	print_2darray(char **arr);
void	free_2darray(char **arr);

/** Environment functions **/
char	**parse_env(char *envp[]);
char	*concat_path(char *cmd, char *path);
char	*get_cmd(char *cmd, char **path);

/** File Descriptor functions**/
void	dup_fd(int pipe_fd[], int file_fd, int mode);
void	close_pipe(int pipe_fd[]);
int		open_file(char *file_name, char **env, char mode);

/** Error handling functions **/
int	check_access(char *name, int mode);
void	write_error(int mode, char *error_msg);
void	read_error_buffer(char *file_name);
void	print_error(void);

/** Execution Functions */
void    handle_child(char **env, char **av, int pipe_fd[], int mode);

#endif /* PIPEX_H */
