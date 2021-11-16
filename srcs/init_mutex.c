/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:41:17 by mqueguin          #+#    #+#             */
/*   Updated: 2021/11/09 18:55:37 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static	int	ft_init_mutex_second_part(t_info *info)
{
	if (pthread_mutex_init(&info->full_meal, NULL) != 0)
	{
		ft_putstr_fd("Error\nMutex initialization failed\n", 2);
		return (0);
	}
	if (pthread_mutex_init(&info->print_death_mutex, NULL) != 0)
	{
		ft_putstr_fd("Error\nMutex initialization failed\n", 2);
		return (0);
	}
	return (1);
}

int	ft_init_mutex(t_info *info)
{
	if (pthread_mutex_init(&info->dead_mutex, NULL) != 0)
	{
		ft_putstr_fd("Error\nMutex initialization failed\n", 2);
		return (0);
	}
	if (pthread_mutex_init(&info->meal_mutex, NULL) != 0)
	{
		ft_putstr_fd("Error\nMutex initialization failed\n", 2);
		return (0);
	}
	if (pthread_mutex_init(&info->last_meal_mutex, NULL) != 0)
	{
		ft_putstr_fd("Error\nMutex initialization failed\n", 2);
		return (0);
	}
	if (!ft_init_mutex_second_part(info))
		return (0);
	return (1);
}
