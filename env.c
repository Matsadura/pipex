/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:28:13 by zzaoui            #+#    #+#             */
/*   Updated: 2025/01/13 12:43:44 by zzaoui           ###   ########.fr       */
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

/**
 * parse_env - Parses the environment
 * @envp: The 2D array containing the environmental variables
 * Return: 2D array containing PATH variable members
 */
char	**parse_env(char *envp[])
{
	int		i;
	char	**paths;
	const char	*str;

	i = 0;
	while (envp[i])
	{
		str = ft_strnstr(envp[i], "PATH=", 5);
		if (str != NULL)
			break ;
		i++;
	}
	paths = ft_split(str + 5, ':');
	return (paths);
}

/**
 * concat_path - Concatenates the command basename with a env path
 * @cmd: The command basename
 * @path: The env path
 * Return: The concatenation result
 */
char	*concat_path(char *cmd, char *path)
{
	char	*result;
	size_t	len;

	if (cmd == NULL || path == NULL)
		return (NULL);
	len = ft_strlen(cmd) + ft_strlen(path) + 2;
	result = malloc(len);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, path, len);
	ft_strlcat(result, "/", len);
	ft_strlcat(result, cmd, len);
	return (result);
}

int	main(int ac, char **av, char *envp[])
{
	char	*cmd_path;
	char	**paths;
	int		i;

	(void)ac;
	paths = parse_env(envp);
	print_2darray(paths);
	i = 0;
	while (paths[i])
	{
		cmd_path = concat_path(av[1], paths[i]);
		ft_printf("%s\n", cmd_path);
		free(cmd_path);
		i++;
	}
	free_2darray(paths);
	return (0);
}
