/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourkai <rbourkai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:03:08 by rbourkai          #+#    #+#             */
/*   Updated: 2025/07/02 15:46:30 by rbourkai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_data(t_data *data)
{
	if (init_mutexes(data) != 0)
		return (1);
	if (init_philosophers(data) != 0)
		return (1);
	data->simulation_stop = 0;
	return (0);
}

int	init_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->forks)
		return (-1);
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (-1);
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
		return (-1);
	return (0);
}

int	init_philosophers(t_data *data)
{
	int	i;

	data->philosophers = malloc(sizeof(t_philo) * data->nb_philos);
	if (!data->philosophers)
		return (-1);
	i = 0;
	while (i < data->nb_philos)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].meals_eaten = 0;
		data->philosophers[i].eating = 0;
		data->philosophers[i].last_meal_time = 0;
		data->philosophers[i].data = data;
		data->philosophers[i].left_fork = i;
		data->philosophers[i].right_fork = (i + 1) % data->nb_philos;
		i++;
	}
	return (0);
}

void	init_last_meal_time(t_data *data, long long current_time)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->philosophers[i].last_meal_time = current_time;
		pthread_mutex_unlock(&data->death_mutex);
		i++;
	}
}

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_create(&data->philosophers[i].thread, NULL,
				philosopher_routine, &data->philosophers[i]) != 0)
			return (printf("Error: Failed to create thread\n"), -1);
		usleep(100);
		i++;
	}
	return (0);
}
