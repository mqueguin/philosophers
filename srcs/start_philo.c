/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:35:31 by mqueguin          #+#    #+#             */
/*   Updated: 2021/11/16 16:31:55 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static	void	eating(t_philo *philo)
{
	t_info		*info;

	info = philo->info;
	pthread_mutex_lock(&info->forks[philo->fork_l]);
	//if (philo->info->is_dead == 0)
		print_state(philo->id, "has taken a fork", info, 16);
	pthread_mutex_lock(&info->forks[philo->fork_r]);
	//if (philo->info->is_dead == 0)
		print_state(philo->id, "has taken a fork", info, 16);
	pthread_mutex_lock(&info->last_meal_mutex);
	philo->last_meal = get_time_miliseconds();
	pthread_mutex_unlock(&info->last_meal_mutex);
	//if (philo->info->is_dead == 0)
		print_state(philo->id, "is eating", info, 9);
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
		if (!check_dead_full_meal_in_routine(info))
			break ;
		eating(philo);
		//if (info->is_dead == 0)
			print_state(philo->id, "is sleeping", info, 11);
		ft_skip_time(info->time_to_sleep);
		//if (info->is_dead == 0)
			print_state(philo->id, "is thinking", info, 11);
	}
	return (0);
}

static	long long	set_last_meal(t_info *info, int i)
{
	long long	last_meal_v;

	if (info->philo[i].last_meal == 0)
		last_meal_v = info->philo[i].first_meal;
	else
		last_meal_v = info->philo[i].last_meal;
	return (last_meal_v);
}

static	void	alive_or_dead(t_info *info, int i, int j)
{
	while (info->is_dead == 0 || info->meal_ok == 0)
	{
		i = -1;
		j = -1;
		while (++i < info->nb_philo)
		{
			pthread_mutex_lock(&info->last_meal_mutex);
			info->philo[i].last_meal = set_last_meal(info, i);
			if (print_death(info, i) == 1)
			{
				pthread_mutex_lock(&info->print_death_mutex);
				info->print = 1;
				pthread_mutex_unlock(&info->print_death_mutex);
				return ;
			}
			pthread_mutex_unlock(&info->last_meal_mutex);
			pthread_mutex_lock(&info->meal_mutex);
			if (info->philo[i].meal >= info->number_eat
				&& info->number_eat != -1)
			{
				pthread_mutex_unlock(&info->meal_mutex);
				if (++j == info->nb_philo - 1)
				{
					info->meal_ok = 1;
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
