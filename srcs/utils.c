/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:08:52 by mqueguin          #+#    #+#             */
/*   Updated: 2021/10/15 18:48:58 by mqueguin         ###   ########.fr       */
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
	long long i;

	i = get_time_miliseconds();
	while (1)
	{
		if (get_time_miliseconds() - i >= time)
			break;
		usleep(20);
	}

}
