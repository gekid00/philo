/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourkai <rbourkai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:03:53 by rbourkai          #+#    #+#             */
/*   Updated: 2025/07/02 18:47:32 by rbourkai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				left_fork;
	int				right_fork;
	long long		last_meal_time;
	int				meals_eaten;
	int				eating;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	int				simulation_stop;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	t_philo			*philosophers;
}	t_data;

int			parse_args(int ac, char **av, t_data *data);
int			ft_atoi(const char *str, int *result);

long long	get_time(void);
void		ft_usleep(int time_ms);

int			init_data(t_data *data);
int			init_mutexes(t_data *data);
int			init_philosophers(t_data *data);

void		*philosopher_routine(void *arg);
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);
void		print_status(t_philo *philo, char *status);
void		handle_single_philo(t_philo *philo);
void		take_forks(t_philo *philo);
void		start_eating(t_philo *philo);
void		finish_eating(t_philo *philo);
void		release_forks(t_philo *philo);

long long	get_time(void);
void		ft_usleep(int time_ms);
int			is_simulation_finished(t_data *data);
void		pick_forks(t_philo *philo);

void		monitor_philosophers(t_data *data);
int			check_all_ate(t_data *data);
int			is_philo_dead(t_data *data, int i);

int			start_simulation(t_data *data);
void		wait_for_threads(t_data *data);
void		init_last_meal_time(t_data *data, long long current_time);
int			create_threads(t_data *data);

void		cleanup_data(t_data *data);

#endif