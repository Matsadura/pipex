/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:56:43 by zzaoui            #+#    #+#             */
/*   Updated: 2025/01/13 16:21:52 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * parse_env - Parses the environment
 * @envp: The 2D array containing the environmental variables
 * Return: 2D array containing PATH variable members
 */
char	**parse_env(char *envp[])
{
	const char	*str;
	char		**paths;
	int			i;

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

/**
 * check_cmd_exist - Check if the command path exists and is executable
 * @cmd: The command name to check
 */
char	*check_cmd_exist(char *cmd, char **envp)
{
	char	*cmd_path;
	char	**path;
	int		i;

	if (cmd == NULL || envp == NULL)
		return (NULL);
	if (access(cmd, F_OK | X_OK) != -1)
		return (ft_strdup(cmd));
	path = parse_env(envp);
	i = 0;
	while (path[i] != NULL)
	{
		cmd_path = concat_path(cmd, path[i]);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			free_2darray(path);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_2darray(path);
	return (NULL);
}
