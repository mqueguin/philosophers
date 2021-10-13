/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:48:54 by mqueguin          #+#    #+#             */
/*   Updated: 2021/10/13 20:44:40 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct	s_philo
{
	int			forks[2]; // forks[0] : fourchette gauche; forks[1] : fourchette droite
	//Mettre le thread ici
	pthread_t	thread_philo;
}				t_philo;

typedef struct	s_info
{
	int			nb_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_of_eat;
	int			b_number_of_eat;
	t_philo		philo[200]; // 200 est le nombre de philos max possible a gerer
	int			timestamp; // Permet de faire une soustraction pour afficher le temps ecouler en miliseconds
}				t_info;

int		ft_isdigit_str(char *str);


int		start_philo(t_info *philo_info);

/**
 * Fonction de debug
 **/
void	print_struct_info(t_info *philo_info);

#endif
