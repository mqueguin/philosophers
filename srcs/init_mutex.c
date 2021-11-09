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

int	ft_init_mutex(t_info *info)
{
	if (pthread_mutex_init(&info->dead_mutex, NULL) != 0)
	{
		ft_putstr_fd("Error\nInitilisation mutex error\n", 2);
		return (0);
	}
	if (pthread_mutex_init(&info->meal_mutex, NULL) != 0)
	{
		ft_putstr_fd("Error\nInitialisation des mutex error\n", 2);
		return (0);
	}
	if (pthread_mutex_init(&info->last_meal_mutex, NULL) != 0)
	{
		ft_putstr_fd("Error\nInitialisation des mutex error\n", 2);
		return (0);
	}
	if (pthread_mutex_init(&info->full_meal, NULL) != 0)
	{
		ft_putstr_fd("Error\nInitialisation des mutex error\n", 2);
		return (0);
	}
	return (1);
}
