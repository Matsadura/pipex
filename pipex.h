/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:39:28 by zzaoui            #+#    #+#             */
/*   Updated: 2025/01/23 16:25:36 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <sys/wait.h>
# include <errno.h>
# include <string.h>

# define IS_DIR ": Is a directory\n"
# define CMD_404 ": command not found\n"
# define CMD_403 ": permission denied\n"

/** Components structure **/
typedef struct s_pipex
{
	char	**env;
	char	**av;
	int		pipe_fd[2];
}	t_pipex;

void	t_init(t_pipex *strct, char **envp, char **av);

/** 2D Array functions **/

void	print_2darray(char **arr);
void	free_2darray(char **arr);

/** Environment functions **/

char	**parse_env(char *envp[]);
char	*concat_path(char *cmd, char *path);
char	*get_cmd(char *cmd, char **path);

/** File Descriptor functions**/

void	dup_fd(t_pipex strct, char *file_name, int mode);
void	close_pipe(int pipe_fd[]);
int		open_file(char *file_name, t_pipex strct, char mode);

/** Error handling functions **/

void	write_error(int mode, char *error_msg);
void	handle_error_components(char *file_name);
void	print_error(void);
int		check_access(char *name, int mode);

/** Execution Functions */

void	handle_child(t_pipex strct, int mode, int index);

#endif /* PIPEX_H */
