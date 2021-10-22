/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 20:35:31 by mqueguin          #+#    #+#             */
/*   Updated: 2021/10/22 15:20:50 by mqueguin         ###   ########.fr       */
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
	print_state(philo->id, "has taken a fork", info, 0);
	pthread_mutex_lock(&info->forks[philo->fork_r]);
	print_state(philo->id, "has taken a fork", info, 0);
	pthread_mutex_lock(&info->last_meal_mutex);
	philo->last_meal = get_time_miliseconds();
	pthread_mutex_unlock(&info->last_meal_mutex);
	print_state(philo->id, "is eating", info, 0);
	usleep(info->time_to_eat * 1000);
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
	int	dead;

	dead = info->is_dead;
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

	ok = info->is_dead;
	meal_ok_v = info->meal_ok;
	long long	last_meal_v;
	int	meal_v;
	int		k = 0;
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
			//meal_v = info->philo[i].meal;
			//if (k == 0)
			//{
				//last_meal_v = info->philo[i].first_meal;
				//printf("Valeur de first_meal dans alive_or_dead : %lld\n", info->philo[i].first_meal);
			//}
			//else
			//	last_meal_v = info->philo[i].last_meal;
			if ((get_time_miliseconds() - last_meal_v)
				>= info->time_to_die)
			{
				print_state(info->philo[i].id, "died", info, 1);
				ok = 1;
				return ;
			}
			pthread_mutex_lock(&info->meal_mutex);
			meal_v = info->philo[i].meal;
			pthread_mutex_unlock(&info->meal_mutex);
			if (meal_v >= info->number_of_eat
				&& info->number_of_eat != -1)
			{
				j++;
				if (j == info->nb_philo - 1)
				{
					meal_ok_v = 1;
					return ;
				}
			}
		}
		k++;
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
			philo[i].first_meal = get_time_miliseconds();
	}
	alive_or_dead(info, -1, 0);
	usleep(1500);
	i = -1;
	while (++i < info->nb_philo)
		pthread_detach(info->philo[i].thread_philo);
	return (1);
}
