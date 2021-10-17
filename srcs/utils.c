/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:08:52 by mqueguin          #+#    #+#             */
/*   Updated: 2021/10/17 18:42:33 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_isdigit_str(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!((str[i] >= '0') && (str[i] <= '9')))
			return (0);
	return (1);
}

void	ft_skip_time(int time)
{
	long long	i;

	i = get_time_miliseconds();
	while (1)
	{
		if (get_time_miliseconds() - i >= time)
			break ;
		usleep(20);
	}
}

long	ft_atoi(const char *str)
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

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
	{
		while (*s)
		{
			write(fd, &*s, 1);
			s++;
		}
	}
}

int	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			write(fd, &s[i], 1);
			i++;
		}
		write(fd, "\n", 1);
	}
	return (0);
}
