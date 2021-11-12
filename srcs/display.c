/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:43:08 by mqueguin          #+#    #+#             */
/*   Updated: 2021/11/10 18:17:06 by mqueguin         ###   ########.fr       */
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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	print_death(t_info *info, int i)
{
	if ((get_time_miliseconds() - info->philo[i].last_meal)
		>= info->time_to_die)
	{
		pthread_mutex_lock(&info->dead_mutex);
		info->is_dead = 1;
		pthread_mutex_unlock(&info->dead_mutex);
		print_state(info->philo[i].id, "died", info, 4);
		return (1);
	}
	return (0);
}

int	print_state(int id, char *state, t_info *info, int len)
{
	pthread_mutex_lock(&info->display);
	write(1, "[ ", 2);
	ft_putnbr_fd((long long)(get_time_miliseconds() - info->timestamp), 1);
	write(1, " ]", 2);
	write(1, " Philo ", 7);
	ft_putnbr_fd(id + 1, 1);
	write(1, " ", 1);
	write(1, state, len);
	ft_putchar_fd('\n', 1);
	if (ft_strncmp("died", state, 4) != 0)
	{
		pthread_mutex_unlock(&info->display);
		return (1);
	}
	return (0);
}
