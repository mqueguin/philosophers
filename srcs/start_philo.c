/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:35:31 by mqueguin          #+#    #+#             */
/*   Updated: 2021/10/21 17:48:12 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static	void	ft_caca(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->last_meal_mutex);
	philo->last_meal = get_time_miliseconds();
	pthread_mutex_unlock(&philo->info->last_meal_mutex);
}

static	void	eating(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	pthread_mutex_lock(&info->forks[philo->fork_l]);
	print_state(philo->id, "has taken a fork", info, 0);
	pthread_mutex_lock(&info->forks[philo->fork_r]);
	print_state(philo->id, "has taken a fork", info, 0);
	//pthread_mutex_lock(&info->last_meal_mutex);
	//philo->last_meal = get_time_miliseconds();
	ft_caca(philo);
	//pthread_mutex_unlock(&info->last_meal_mutex);
	print_state(philo->id, "is eating", info, 0);
	usleep(info->time_to_eat * 1000);
	//pthread_mutex_lock(&info->meal_mutex);
	philo->meal++;
	//pthread_mutex_unlock(&info->meal_mutex);
	//pthread_mutex_unlock(&info->dead_mutex);
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
		usleep(10000);
	int	dead;

	pthread_mutex_lock(&info->dead_mutex);
	dead = info->is_dead;
	pthread_mutex_unlock(&info->dead_mutex);
	while (dead == 0 || philo->meal <= info->number_of_eat)
	{
		eating(philo);
		print_state(philo->id, "is sleeping", info, 0);
		usleep(info->time_to_sleep * 1000);
		print_state(philo->id, "is thinking", info, 0);
	}
	return (0);
}

static	void	alive_or_dead(t_info *info, int i, int j)
{
	int ok;
	int	meal_ok_v;

	//pthread_mutex_lock(&info->dead_mutex);
	ok = info->is_dead;
	//pthread_mutex_unlock(&info->dead_mutex);
	//pthread_mutex_lock(&info->meal_ok_mutex);
	meal_ok_v = info->meal_ok;
	int	last_meal_v = info->philo[i].last_meal;
	int	meal_v = info->philo[i].meal;
	//pthread_mutex_unlock(&info->meal_ok_mutex);

	while (ok == 0 || meal_ok_v == 0)
	{
		i = -1;
		j = 0;
		while (++i < info->nb_philo)
		{
			if ((get_time_miliseconds() - last_meal_v)
				>= info->time_to_die)
			{
				print_state(info->philo[i].id, "died", info, 1);
				//pthread_mutex_lock(&info->dead_mutex);
				ok = 1;
				//info->is_dead = 1;
				//pthread_mutex_unlock(&info->dead_mutex);
				return ;
			}
			if (meal_v >= info->number_of_eat
				&& info->number_of_eat != -1)
			{
				j++;
				if (j == info->nb_philo - 1)
				{
					//pthread_mutex_lock(&info->meal_ok_mutex);
					meal_ok_v = 1;
					//pthread_mutex_lock(&info->meal_ok_mutex);
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
		//philo[i].last_meal = get_time_miliseconds();
		ft_caca(&philo[i]);
	}
	alive_or_dead(info, -1, 0);
	usleep(1500);
	i = -1;
	while (++i < info->nb_philo)
		pthread_detach(info->philo[i].thread_philo);
	return (1);
}
