#include <stdio.h>
#include "libft/libft.h"

//char **parse_env(char *envp[])
//{
//}


int	main(int ac, char **av, char *envp[])
{
	int i;

	(void)ac;
	(void)av;
	i = 0;
	const char *str;
	char **paths;
	while (envp[i])
	{
		str = ft_strnstr(envp[i], "PATH=", 5);
		if (str != NULL)
		{
			printf("STR: %s\n", str);
			break;
		}
		//printf("%s\n", envp[i]);
		i++;
	}
	paths = ft_split(str + 5, ':');
	i = 0;
	while (paths[i])
	{
		printf("%s\n", paths[i]);
		i++;
	}
	return (0);
}
