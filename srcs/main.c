/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourkai <rbourkai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:51:23 by rbourkai          #+#    #+#             */
/*   Updated: 2025/07/02 18:41:02 by rbourkai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

int	start_simulation(t_data *data)
{
	long long	current_time;

	current_time = get_time();
	data->start_time = current_time;
	init_last_meal_time(data, current_time);
	return (create_threads(data));
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!is_simulation_finished(philo->data))
	{
		philo_eat(philo);
		if (is_simulation_finished(philo->data))
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	wait_for_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_join(data->philosophers[i].thread, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	data.forks = NULL;
	data.philosophers = NULL;
	data.simulation_stop = 0;
	if (parse_args(ac, av, &data) != 0)
		return (1);
	if (init_data(&data) != 0)
		return (cleanup_data(&data), 1);
	if (start_simulation(&data) != 0)
		return (cleanup_data(&data), 1);
	monitor_philosophers(&data);
	wait_for_threads(&data);
	return (cleanup_data(&data), 0);
}
