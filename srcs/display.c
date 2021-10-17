/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:43:08 by mqueguin          #+#    #+#             */
/*   Updated: 2021/10/17 18:29:42 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	print_state(int id, char *state, t_info *info, int dead)
{
	pthread_mutex_lock(&info->display);
	printf("[ %s%lld%s ] philo: %d %s\n", GREEN,
		(get_time_miliseconds() - info->timestamp), NC, id, state);
	if (dead == 0)
		pthread_mutex_unlock(&info->display);
}
