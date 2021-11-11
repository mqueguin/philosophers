/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:35:31 by mqueguin          #+#    #+#             */
/*   Updated: 2021/11/10 18:32:53 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static	void	eating(t_philo *philo)
{
	t_info		*info;

	info = philo->info;
	pthread_mutex_lock(&info->forks[philo->fork_l]);
	print_state(philo->id, "has taken a fork", info, 16);
	pthread_mutex_lock(&info->forks[philo->fork_r]);
	print_state(philo->id, "has taken a fork", info, 16);
	pthread_mutex_lock(&info->last_meal_mutex);
	philo->last_meal = get_time_miliseconds();
	pthread_mutex_unlock(&info->last_meal_mutex);
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
		print_state(philo->id, "is sleeping", info, 11);
		ft_skip_time(info->time_to_sleep);
		print_state(philo->id, "is thinking", info, 11);
	}
	return (0);
}

static	int	lock_mutex_last_meal_and_meal(t_info *info,
		int is_dead, int full_meal_v, int i_j[2])
{
	long long	last_meal_v;

	pthread_mutex_lock(&info->last_meal_mutex);
	if (info->philo[i_j[0]].last_meal == 0)
		last_meal_v = info->philo[i_j[0]].first_meal;
	else
		last_meal_v = info->philo[i_j[0]].last_meal;
	pthread_mutex_unlock(&info->last_meal_mutex);
	if ((get_time_miliseconds() - last_meal_v) >= info->time_to_die)
	{
		is_dead = 1;
		return (print_state(info->philo[i_j[0]].id, "died", info, 4));
	}
	pthread_mutex_lock(&info->meal_mutex);
	if (info->philo[i_j[0]].meal >= info->number_eat && info->number_eat != -1)
	{
		pthread_mutex_unlock(&info->meal_mutex);
		if (++i_j[1] == info->nb_philo - 1)
		{
			full_meal_v = 1;
			return (0);
		}
	}
	pthread_mutex_unlock(&info->meal_mutex);
	return (1);
}

static	void	alive_or_dead(t_info *info, int i_j[2])
{
	int			is_dead;
	int			full_meal_v;

	is_dead = info->is_dead;
	full_meal_v = info->meal_ok;
	while (is_dead == 0 || full_meal_v == 0)
	{
		i_j[0] = -1;
		i_j[1] = 0;
		while (++i_j[0] < info->nb_philo)
		{
			if (!lock_mutex_last_meal_and_meal(info,
					is_dead, full_meal_v, i_j))
				return ;
		}
	}
}

int	start_philo(t_info *info)
{
	int		i;
	t_philo	*philo;
	int		i_j[2];

	i_j[0] = -1;
	i_j[1] = 0;
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
	alive_or_dead(info, i_j);
	usleep(1500000);
	i = -1;
	while (++i < info->nb_philo)
		pthread_detach(info->philo[i].thread_philo);
	return (1);
}
