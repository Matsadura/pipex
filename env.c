/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:28:13 by zzaoui            #+#    #+#             */
/*   Updated: 2025/01/13 15:59:30 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "pipex.h"

/**
 * print_2darray - Prints a 2D array
 * @arr: The 2D array
 */
void	print_2darray(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_putstr_fd(arr[i], 1);
		i++;
	}
}

/**
 * free_2darray - Frees a 2D dynamically allocated array
 * @arr: The 2D array
 */
void	free_2darray(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}


int	main(int ac, char **av, char *envp[])
{
	char	*cmd_path;
	int		i;

	(void)ac;
	i = 0;
	cmd_path = check_cmd_exist(av[1], envp);
	ft_printf("%s\n", cmd_path);
	free(cmd_path);
	return (0);
}
