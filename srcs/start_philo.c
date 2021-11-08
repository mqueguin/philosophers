/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:35:31 by mqueguin          #+#    #+#             */
/*   Updated: 2021/10/22 21:29:05 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/*static	void	ft_caca(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->last_meal_mutex);
	philo->last_meal = get_time_miliseconds();
	pthread_mutex_unlock(&philo->info->last_meal_mutex);
}*/

static	void	eating(t_philo *philo)
{
	t_info		*info;

	info = philo->info;
	pthread_mutex_lock(&info->forks[philo->fork_l]);
	print_state(philo->id, "has taken a fork", info, 0, 16);
	pthread_mutex_lock(&info->forks[philo->fork_r]);
	print_state(philo->id, "has taken a fork", info, 0, 16);
	pthread_mutex_lock(&info->last_meal_mutex);
	philo->last_meal = get_time_miliseconds(); //creer 200 variables last meal via le numero des philos / creer 200 mutex pour last_meal
	pthread_mutex_unlock(&info->last_meal_mutex);
	print_state(philo->id, "is eating", info, 0, 9);
	ft_skip_time(info->time_to_eat);
	pthread_mutex_lock(&info->meal_mutex);
	philo->meal++;
	pthread_mutex_unlock(&info->meal_mutex);
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
	while (1)
	{
		pthread_mutex_lock(&info->dead_mutex);
		if (info->is_dead == 1)
			break ;
		pthread_mutex_unlock(&info->dead_mutex);
		pthread_mutex_lock(&info->full_meal);
		if (info->meal_ok == 1)
		{
			pthread_mutex_unlock(&info->full_meal);
			break ;
		}
		pthread_mutex_unlock(&info->full_meal);
		eating(philo);
		print_state(philo->id, "is sleeping", info, 0, 11);
		ft_skip_time(info->time_to_sleep);
		print_state(philo->id, "is thinking", info, 0, 11);
	}
	return (0);
}

static	void	alive_or_dead(t_info *info, int i, int j)
{
	int ok;
	int	meal_ok_v;
	long long	last_meal_v;

	ok = info->is_dead;
	meal_ok_v = info->meal_ok;
	while (ok == 0 || meal_ok_v == 0)
	{
		i = -1;
		j = 0;
		while (++i < info->nb_philo)
		{
			pthread_mutex_lock(&info->last_meal_mutex);
			if (info->philo[i].last_meal == 0)
				last_meal_v = info->philo[i].first_meal;
			else
				last_meal_v = info->philo[i].last_meal;
			pthread_mutex_unlock(&info->last_meal_mutex);
			if ((get_time_miliseconds() - last_meal_v)
				>= info->time_to_die)
			{
				print_state(info->philo[i].id, "died", info, 1, 4);
				ok = 1;
				return ;
			}
			pthread_mutex_lock(&info->meal_mutex);
			if (info->philo[i].meal >= info->number_of_eat
				&& info->number_of_eat != -1)
			{
				pthread_mutex_unlock(&info->meal_mutex);
				j++;
				if (j == info->nb_philo - 1)
				{
					meal_ok_v = 1;
					return ;
				}
			}
			pthread_mutex_unlock(&info->meal_mutex);
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
			philo[i].first_meal = get_time_miliseconds();
	}
	alive_or_dead(info, -1, 0);
	usleep(1500000);
	i = -1;
	while (++i < info->nb_philo)
		pthread_detach(info->philo[i].thread_philo);
	return (1);
}
