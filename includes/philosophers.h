/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:48:54 by mqueguin          #+#    #+#             */
/*   Updated: 2021/10/22 16:48:49 by mqueguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define RED "\033[0;31m"
# define CYAN "\033[0;36m"
# define GREEN "\033[0;32m"
# define NC "\033[0m"

typedef struct s_philo
{
	int				id;
	int				fork_r;
	int				fork_l;
	struct s_info	*info;
	pthread_t		thread_philo;
	int				meal;
	long long		last_meal;
	long long		first_meal;
}				t_philo;

typedef struct s_info
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_eat;
	int				meal_ok;
	int				b_number_of_eat;
	t_philo			philo[200];
	long long		timestamp;
	int				is_dead;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	display;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	forks[200];
}				t_info;

int			ft_isdigit_str(char *str);
int			start_philo(t_info *philo_info);
void		ft_skip_time(int time);
void		print_state(int id, char *state, t_info *info, int dead);
long long	get_time_miliseconds(void);
int			ft_putendl_fd(char *s, int fd);
void		ft_putstr_fd(char *s, int fd);
long		ft_atoi(const char *str);

#endif
