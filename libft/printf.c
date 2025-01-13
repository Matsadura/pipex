/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaoui <zzaoui@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:54:58 by zzaoui            #+#    #+#             */
/*   Updated: 2024/12/12 12:20:45 by zzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * ft_printf - Writes output to stdout
 * @str: the string to parse
 * Return: the number of written bytes
 */
int	ft_printf(const char *str, ...)
{
	va_list	args;
	t_spec	*spec;

	int (written), (i), (count);
	if (str == NULL)
		return (-1);
	written = 0;
	i = 0;
	va_start(args, str);
	init(&spec);
	while (str[i] != '\0')
	{
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			count = get_spec_func(str[i + 1], spec, args);
			i += 1;
		}
		else
			count = write(1, &str[i], 1);
		if (count == -1)
			return (va_end(args), -1);
		written += count;
		i++;
	}
	return (va_end(args), written);
}
