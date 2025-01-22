/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:56:43 by zzaoui            #+#    #+#             */
/*   Updated: 2025/01/22 15:22:25 by zzaoui           ###   ########.fr       */
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

	if (envp == NULL)
		return (NULL);
	i = 0;
	str = NULL;
	while (envp[i])
	{
		str = ft_strnstr(envp[i], "PATH=", 5);
		if (str != NULL)
			break ;
		i++;
	}
	if (str == NULL)
		return (NULL);
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
 * get_cmd - Check if the command path exists and is executable
 * 			and returns the correct one if it exists
 * @cmd: The command name to check
 * Return: The correct command otherwise NULL
 */
char	*get_cmd(char *cmd, char **path)
{
	char	*cmd_path;
	int		i;

	if (open(cmd, O_DIRECTORY) != -1)
		return (NULL);
	if (access(cmd, F_OK | X_OK) != -1)
		return (ft_strdup(cmd));
	if (cmd == NULL || path == NULL)
		return (NULL);
	i = 0;
	while (path[i] != NULL)
	{
		cmd_path = concat_path(cmd, path[i]);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}
