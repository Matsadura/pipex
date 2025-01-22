/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:29:52 by zzaoui            #+#    #+#             */
/*   Updated: 2025/01/21 20:05:44 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
