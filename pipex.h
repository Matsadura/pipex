/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:39:28 by zzaoui            #+#    #+#             */
/*   Updated: 2025/01/13 16:22:54 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <sys/wait.h>

/** 2D Array functions **/
void	print_2darray(char **arr);
void	free_2darray(char **arr);

/** Environment functions **/
char	**parse_env(char *envp[]);
char	*concat_path(char *cmd, char *path);
char	*check_cmd_exist(char *cmd, char **envp);

#endif /* PIPEX_H */
