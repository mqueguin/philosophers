/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:35:31 by mqueguin          #+#    #+#             */
/*   Updated: 2021/10/15 14:17:04 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

//pthread_mutex_t lock;

void	*routine(void *philo_s)
{
	t_philo		*philo;
	t_info		*info;

	/* pthread_mutex_lock(&lock); */
	philo = (t_philo *)philo_s;
	info = philo->info;
	//printf("Valeur de number_of_eat : %d\n", info->number_of_eat);
	ft_putstr_fd("Je suis un philosophe\n", 1);
	printf("Id du philo sur lequel on est : %d\n", philo->id);
	print_struct_info(info);
	
	//printf("Valeur de nb_philo : %d\n", info->nb_philo);
	//printf("Valeur de time_to_eat : %d\n", info->time_to_eat);
	/* pthread_mutex_unlock(&lock); */
	return (0);
}

int	start_philo(t_info *info)
{
	int		ret;
	int		i;
	t_philo	*philo;

	philo = info->philo;
	i = -1;
	//print_struct_info(philo->info);

	/* if (pthread_mutex_init(&lock, NULL) != 0)
	{
		ft_putstr_fd("Error\nImpossible d'initialiser le mutex\n", 2);
		return (0);
	} */
	while (++i < info->nb_philo)
	{
		ret = pthread_create(&(philo[i].thread_philo), NULL, routine, &(philo[i]));
		if (ret != 0)
		{
			ft_putstr_fd("Error\nImpossible de creer les threads\n", 2);
			return (0);
		}
		usleep(10000);
	}
	//pthread_mutex_destroy(&lock);
	while (1)
		;
	return (1);
}