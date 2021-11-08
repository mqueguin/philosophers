/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 20:05:35 by mqueguin          #+#    #+#             */
/*   Updated: 2021/11/08 20:07:31 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

static char    *ft_jump_zero(char *s)
{
    while (*s++ == '0')
        ;
    return (s);
}

long	ft_atoi(char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	if (str[0] == '\0')
		return (-1);
	str = ft_jump_zero(str);
	if (ft_strlen(str) > 10)
		return (-1);
	else if (ft_strlen(str) == 10)
		if (ft_strncmp(str, "2147483647", 10) > 0)
			return (-1);
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10 + ((int)str[i++] - '0');
	return (result);
}