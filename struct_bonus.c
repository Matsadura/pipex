/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:45:09 by zzaoui            #+#    #+#             */
/*   Updated: 2025/01/21 18:04:28 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	t_init(t_pipex *strct, char **envp, char **av)
{
	strct->env = parse_env(envp);
	strct->av = av;
	strct->status = 0;
}
