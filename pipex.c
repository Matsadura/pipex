/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:21:38 by zzaoui            #+#    #+#             */
/*   Updated: 2025/01/22 16:19:36 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char *envp[])
{
	t_pipex	strct;
	pid_t	id1;
	pid_t	id2;
	int		stat;

	if (ac != 5)
		return (ft_printf("Usage: ./pipex in cmd1 cmd2 out\n"), -1);
	t_init(&strct, envp, av);
	if (pipe(strct.pipe_fd) == -1)
		exit(-1);
	id1 = fork();
	if (id1 == -1)
		exit(-1);
	if (id1 == 0)
		handle_child(strct, STDIN_FILENO, 1);
	id2 = fork();
	if (id2 == -1)
		exit(-1);
	if (id2 == 0)
		handle_child(strct, STDOUT_FILENO, 4);
	stat = 0;
	cleanup(strct, id1, id2, &stat);
	return (WEXITSTATUS(stat));
}
