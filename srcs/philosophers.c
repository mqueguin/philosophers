/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 13:33:54 by mqueguin          #+#    #+#             */
/*   Updated: 2021/10/15 19:04:53 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	print_struct_info(t_info *info)
{
	printf("Valeur de nb_philo : %d\n", info->nb_philo);
	printf("Valeur de time_to_die : %d\n", info->time_to_die);
	printf("Valeur de time_to_eat : %d\n", info->time_to_eat);
	printf("Valeur de time_to_sleep : %d\n", info->time_to_sleep);
	printf("Valeur de b_number_of_eat : %d\n", info->b_number_of_eat);
	printf("Valeur de number_of_eat : %d\n", info->number_of_eat);
}

long long	get_time_miliseconds(void)
{
	struct		timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

static	int	ft_init_philo(t_info *philo_info)
{
	int	i;

	i = philo_info->nb_philo - 1;
	while (i >= 0)
	{
		if (pthread_mutex_init(&philo_info->forks[i], NULL) != 0)
		{
			ft_putstr_fd("Error\nInitialisation des mutex\n", 2);
			return (0);
		}
		philo_info->philo[i].id = i;
		philo_info->philo[i].fork_l = i;
		philo_info->philo[i].fork_r = ((philo_info->philo[i].id + 1) % philo_info->nb_philo);
		philo_info->philo[i].info = philo_info;
		philo_info->philo[i].last_meal = 0;
		philo_info->philo[i].meal = 0;
		i--;
	}
	if (pthread_mutex_init(&philo_info->display, NULL) != 0)
	{
		ft_putstr_fd("Error\nInitialisation du mutex display\n", 2);
		return (0);
	}
	return (1);
}

static int	recover_philo_info(char **av, t_info *philo_info)
{
	philo_info->nb_philo = ft_atoi(av[1]);
	philo_info->time_to_die = ft_atoi(av[2]);
	philo_info->time_to_eat = ft_atoi(av[3]);
	philo_info->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
	{
		philo_info->b_number_of_eat = 1;
		philo_info->number_of_eat = ft_atoi(av[5]);
	}
	else
	{
		philo_info->b_number_of_eat = 0;
		philo_info->number_of_eat = -1;
	}
	if (!ft_init_philo(philo_info))
		return (0);
	philo_info->meal_ok = 0;
	return (1);
}

static int	parse_arg(char **av, t_info *philo_info)
{
	int i;

	i = 0;
	while (av[++i])
	{
		if (!ft_isdigit_str(av[i]) || ft_atoi(av[i]) < 1)
		{
			ft_putstr_fd("Error\n", 2);
			return (0);
		}
	}
	recover_philo_info(av, philo_info);
	return (1);
}

int	main(int ac, char **av)
{
	t_info	philo_info;

	philo_info.is_dead = 0;
	if (ac != 5 && ac != 6)
	{
		ft_putendl_fd("Error", 2);
		return (-1);
	}
	if (!parse_arg(av, &philo_info))
		return (-1);
	/*for (int i = 0; i < 10; i++)
	{
		usleep(1000);
		printf("Heure : %lld\n", get_time_miliseconds() - timestamp);
	}*/
	//print_struct_info(&philo_info);
	/* int i = -1;
	int ret; */
	/* while (++i < philo_info.nb_philo)
	{
		ret = pthread_create(philo_info.philo[i], NULL, routine)
	} */
	if (!start_philo(&philo_info))
		return (-1);
	return (0);
}
