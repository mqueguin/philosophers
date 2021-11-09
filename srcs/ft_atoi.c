/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 20:05:35 by mqueguin          #+#    #+#             */
/*   Updated: 2021/11/09 18:14:06 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_check_overflow(char **av)
{
	int	i;
	long	tmp;

	i = 0;

	while (av[++i])
	{
		tmp = ft_atoi(av[i]);
		if (tmp > 2147483647 || tmp < -2147483648)
		{
			ft_putstr_fd("Error\nInvalid number\n", 2);
			return (0);
		}
	}
	return (1);
}

long	ft_atoi(char *str)
{
	int		i;
	int		negative;
	long	result;

	i = 0;
	negative = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			negative *= -1;
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10 + ((int)str[i++] - '0');
	if (result < 0 && (negative == 1))
		return (-1);
	else if (result < 0 && (negative == -1))
		return (0);
	return (result * negative);
}
