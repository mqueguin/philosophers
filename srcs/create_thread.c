/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:35:31 by mqueguin          #+#    #+#             */
/*   Updated: 2021/10/17 18:29:06 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

//pthread_mutex_t lock;

static	void	eating(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	pthread_mutex_lock(&info->forks[philo->fork_l]);
	print_state(philo->id, "has taken a fork", info, 0);
	pthread_mutex_lock(&info->forks[philo->fork_r]);
	print_state(philo->id, "has taken a fork", info, 0);
	philo->last_meal = get_time_miliseconds();
	print_state(philo->id, "is eating", info, 0);
	ft_skip_time(info->time_to_eat);
	philo->meal++;
	pthread_mutex_unlock(&info->forks[philo->fork_l]);
	pthread_mutex_unlock(&info->forks[philo->fork_r]);
}

static	void	*routine(void *philo_s)
{
	t_philo		*philo;
	t_info		*info;

	philo = (t_philo *)philo_s;
	info = philo->info;
	if (philo->id % 2)
		usleep(15000);
	while (info->is_dead == 0 || philo->meal <= info->number_of_eat)
	{
		eating(philo);
		print_state(philo->id, "is sleeping", info, 0);
		ft_skip_time(info->time_to_sleep);
		print_state(philo->id, "is thinking", info, 0);
	}
	return (0);
}

static	void	alive_or_dead(t_info *info, int i, int j)
{
	while (info->is_dead == 0 || info->meal_ok == 0)
	{
		i = -1;
		j = 0;
		while (++i < info->nb_philo)
		{
			if ((get_time_miliseconds() - info->philo[i].last_meal)
				>= info->time_to_die)
			{
				print_state(info->philo[i].id, "died", info, 1);
				info->is_dead = 1;
				return ;
			}
			if (info->philo[i].meal >= info->number_of_eat
				&& info->number_of_eat != -1)
			{
				j++;
				if (j == info->nb_philo - 1)
				{
					info->meal_ok = 1;
					return ;
				}
			}
		}
	}
}

int	start_philo(t_info *info)
{
	int		i;
	t_philo	*philo;

	philo = info->philo;
	i = -1;
	info->timestamp = get_time_miliseconds();
	while (++i < info->nb_philo)
	{
		if (pthread_create(&(philo[i].thread_philo), NULL, routine,
				&(philo[i])) != 0)
		{
			ft_putstr_fd("Error\nImpossible de creer les threads\n", 2);
			return (0);
		}
		philo[i].last_meal = get_time_miliseconds();
	}
	alive_or_dead(info, -1, 0);
	usleep(1500);
	i = -1;
	while (++i < info->nb_philo)
		pthread_detach(info->philo[i].thread_philo);
	return (1);
}
