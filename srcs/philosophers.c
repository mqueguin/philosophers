/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 13:33:54 by mqueguin          #+#    #+#             */
/*   Updated: 2021/11/09 17:17:38 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static	int	ft_init_philo(t_info *info)
{
	int	i;

	i = info->nb_philo - 1;
	while (i >= 0)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
		{
			ft_putstr_fd("Error\nInitialisation des mutex\n", 2);
			return (0);
		}
		info->philo[i].id = i;
		info->philo[i].fork_l = i;
		info->philo[i].fork_r = ((info->philo[i].id + 1) % info->nb_philo);
		info->philo[i].info = info;
		info->philo[i].last_meal = 0;
		info->philo[i].meal = 0;
		info->philo[i].first_meal = 0;
		i--;
	}
	if (pthread_mutex_init(&info->display, NULL) != 0)
	{
		ft_putstr_fd("Error\nInitialisation du mutex display\n", 2);
		return (0);
	}
	return (1);
}

static int	ft_init_mutex_dead_or_nb_meal(t_info *info)
{
	if (pthread_mutex_init(&info->dead_mutex, NULL) != 0)
	{
		ft_putstr_fd("Error\nInitilisation mutex error\n", 2);
		return (0);
	}
	if (pthread_mutex_init(&info->meal_mutex, NULL) != 0)
	{
		ft_putstr_fd("Error\nInitialisation des mutex error\n", 2);
		return (0);
	}
	if (pthread_mutex_init(&info->last_meal_mutex, NULL) != 0)
	{
		ft_putstr_fd("Error\nInitialisation des mutex error\n", 2);
		return (0);
	}
	if (pthread_mutex_init(&info->full_meal, NULL) != 0)
	{
		ft_putstr_fd("Error\nInitialisation des mutex error\n", 2);
		return (0);
	}
	return (1);
}

static int	recover_info(char **av, t_info *info)
{
	if (!ft_check_overflow(av))
		return (0);
	info->nb_philo = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
	{
		info->b_number_of_eat = 1;
		info->number_of_eat = ft_atoi(av[5]);
	}
	else
	{
		info->b_number_of_eat = 0;
		info->number_of_eat = -1;
	}
	if (!ft_init_philo(info))
		return (0);
	if (!ft_init_mutex_dead_or_nb_meal(info))
		return (0);
	info->meal_ok = 0;
	return (1);
}

static int	parse_arg(char **av, t_info *info)
{
	int	i;

	i = 0;
	while (av[++i])
	{
		if (!ft_isdigit_str(av[i]))
		{
			ft_putstr_fd("Error\n", 2);
			return (0);
		}
	}
	if (!recover_info(av, info))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_info	info;

	info.is_dead = 0;
	if (ac != 5 && ac != 6)
	{
		ft_putendl_fd("Error\nThere must be at least 5 or 6 arguments", 2);
		return (-1);
	}
	if (!parse_arg(av, &info))
		return (-1);
	printf("J ai passer le parse arg\n");
	printf("Valeur de time_to_eat: %d / time_to_death: %d / time_to_sleep: %d \n", info.time_to_eat, info.time_to_die, info.time_to_sleep);
	if (!start_philo(&info))
		return (-1);
	return (0);
}
