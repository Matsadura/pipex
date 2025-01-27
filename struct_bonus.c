/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:45:09 by zzaoui            #+#    #+#             */
/*   Updated: 2025/01/27 20:29:04 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/**
 * t_init - Structure initialiazer
 * @strct: Pointer to the main component structure
 */
void	t_init(t_pipex *strct, char **envp, int ac, char **av)
{
	strct->env = parse_env(envp);
	strct->ncmd = ac - 3;
	strct->av = av;
	strct->status = 0;
	strct->old_pipe = -1;
	strct->in_fd = -1;
	strct->out_fd = -1;
	strct->infile = av[1];
	strct->outfile = av[ac - 1];
	strct->delim = "dummy";
	strct->out_perms = O_CREAT | O_WRONLY | O_TRUNC;
	strct->is_hdoc = FALSE;
}
