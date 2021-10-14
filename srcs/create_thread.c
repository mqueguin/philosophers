/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:35:31 by mqueguin          #+#    #+#             */
/*   Updated: 2021/10/14 12:22:50 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*routine(void *philo_s)
{
	t_philo		*philo;
	//t_info		*info;

	philo = (t_philo *)philo_s;
	ft_putstr_fd("Je suis un philosophe\n", 1);
	printf("Valeur de nb_philo : %d\n", philo->info->nb_philo);
	return (philo);
}

int	start_philo(t_info *philo_info)
{
	int	ret;
	int	i;

	i = -1;
	print_struct_info(philo_info);
	while (++i < philo_info->nb_philo)
	{
		ret = pthread_create(&(philo_info->philo[i].thread_philo), NULL, routine, &philo_info->philo[i]);
		if (ret != 0)
		{
			ft_putstr_fd("Error\nImpossible de creer les threads\n", 2);
			return (0);
		}
	}
	while (1)
		;
	return (1);
}