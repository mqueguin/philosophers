/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:20:43 by mqueguin          #+#    #+#             */
/*   Updated: 2021/11/10 18:16:12 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	check_dead_full_meal_in_routine(t_info *info)
{
	pthread_mutex_lock(&info->dead_mutex);
	if (info->is_dead == 1)
		return (0);
	pthread_mutex_unlock(&info->dead_mutex);
	pthread_mutex_lock(&info->full_meal);
	if (info->meal_ok == 1)
	{
		pthread_mutex_unlock(&info->full_meal);
		return (0);
	}
	pthread_mutex_unlock(&info->full_meal);
	return (1);
}
