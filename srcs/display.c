/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:43:08 by mqueguin          #+#    #+#             */
/*   Updated: 2021/10/15 18:27:15 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	print_state(int id, char *state, t_info *info, int dead)
{
	pthread_mutex_lock(&info->display);
	printf("[ %lld ] philo: %d %s\n", (get_time_miliseconds() - info->timestamp), id, state);
	//ft_putnbr_fd((get_time_miliseconds() - info->timestamp), 1);
	//ft_putchar_fd('\n', 1);
	if (dead == 0)
		pthread_mutex_unlock(&info->display);
}