/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:43:08 by mqueguin          #+#    #+#             */
/*   Updated: 2021/10/22 15:01:16 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long int	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb = nb * -1;
	}
	if (nb >= 10)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putchar_fd(nb % 10 + 48, fd);
	}
	if (nb < 10)
		ft_putchar_fd(nb + 48, fd);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	print_state(int id, char *state, t_info *info, int dead, int len)
{
	pthread_mutex_lock(&info->display);
	write(2, "[ ", 2);
	ft_putnbr_fd((long long)(get_time_miliseconds() - info->timestamp), 1);
	write(2, " ]", 2);
	write(1, " Philo ", 7);
	ft_putnbr_fd(id + 1, 1);
	write(1, " ", 1);
	write(1, state, len);
	ft_putchar_fd('\n', 1);
	if (dead == 0)
		pthread_mutex_unlock(&info->display);
}
