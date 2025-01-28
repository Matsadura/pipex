/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:39:28 by zzaoui            #+#    #+#             */
/*   Updated: 2025/01/27 20:22:16 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft/libft.h"
# include <sys/wait.h>
# include <errno.h>
# include <string.h>

# define IS_DIR ": Is a directory\n"
# define CMD_404 ": command not found\n"
# define CMD_403 ": permission denied\n"

# define TRUE 1
# define FALSE 0

# define READ_END 0
# define WRITE_END 1
# define STDIN 0
# define STDOUT 1
# define STDERR 2

/** Components structure **/
typedef struct s_pipex
{
	char	**env;
	char	**av;
	char	*delim;
	char	*infile;
	char	*outfile;
	char	*here_doc_file;
	int		out_perms;
	int		ncmd;
	int		pipe_fd[2];
	int		status;
	int		old_pipe;
	int		in_fd;
	int		out_fd;
	int		is_hdoc;
}	t_pipex;

void	t_init(t_pipex *strct, char **envp, int ac, char **av);

/** 2D Array functions **/

void	print_2darray(char **arr);
void	free_2darray(char **arr);

/** Environment functions **/

char	**parse_env(char *envp[]);
char	*concat_path(char *cmd, char *path);
char	*get_cmd(char *cmd, char **path);

/** File Descriptor functions**/

void	dup_and_close(int fd1, int fd2, int mode);
void	dup_and_close_file(int fd, int mode);
int		open_input_file(t_pipex strct);
int		open_output_file(t_pipex strct);

/** Error handling functions **/

void	put_and_free(char *err);
void	cleanup(t_pipex *strct, pid_t pid);
void	check_pipe(int pipe_return, t_pipex strct);
int		check_access(char *name);
pid_t	fork_and_check(t_pipex strct);

/** Execution Functions */

void	execute_cmd(char *arg, char **env, t_pipex strct);
void	handle_child(t_pipex strct, int idx);
void	handle_parent(t_pipex *strct, int idx);

/* Here document Functions */
void	handle_heredoc(t_pipex *strct);
void	put_and_print(char *line, int fd);
void	write_in_heredoc(t_pipex strct);

#endif /* PIPEX_BONUS_H */
