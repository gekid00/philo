/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourkai <rbourkai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:03:13 by rbourkai          #+#    #+#             */
/*   Updated: 2025/07/02 18:38:22 by rbourkai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_all_ate(t_data *data)
{
	int	i;
	int	all_ate;

	if (data->nb_must_eat == -1)
		return (0);
	pthread_mutex_lock(&data->death_mutex);
	if (data->simulation_stop)
		return (pthread_mutex_unlock(&data->death_mutex), 1);
	i = 0;
	all_ate = 1;
	while (i < data->nb_philos)
	{
		if (data->philosophers[i].meals_eaten < data->nb_must_eat)
		{
			all_ate = 0;
			break ;
		}
		i++;
	}
	if (all_ate)
		data->simulation_stop = 1;
	return (pthread_mutex_unlock(&data->death_mutex), all_ate);
}

int	is_philo_dead(t_data *data, int i)
{
	long long	current_time;
	long long	last_meal;
	long long	time_since_last_meal;

	current_time = get_time();
	pthread_mutex_lock(&data->death_mutex);
	if (data->simulation_stop || data->philosophers[i].eating)
		return (pthread_mutex_unlock(&data->death_mutex), 0);
	last_meal = data->philosophers[i].last_meal_time;
	time_since_last_meal = current_time - last_meal;
	if (time_since_last_meal > data->time_to_die)
	{
		data->simulation_stop = 1;
		pthread_mutex_unlock(&data->death_mutex);
		pthread_mutex_lock(&data->print_mutex);
		printf("%lld %d died\n", current_time - data->start_time,
			data->philosophers[i].id);
		fflush(stdout);
		pthread_mutex_unlock(&data->print_mutex);
		return (-1);
	}
	return (pthread_mutex_unlock(&data->death_mutex), 0);
}

void	monitor_philosophers(t_data *data)
{
	int	i;

	while (1)
	{
		if (check_all_ate(data))
			return ;
		i = 0;
		while (i < data->nb_philos)
		{
			if (is_philo_dead(data, i++))
				return ;
		}
		usleep(1000);
	}
}
