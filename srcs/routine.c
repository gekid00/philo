/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourkai <rbourkai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:03:17 by rbourkai          #+#    #+#             */
/*   Updated: 2025/07/02 15:46:30 by rbourkai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_status(t_philo *philo, char *status)
{
	long long	current_time;

	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->death_mutex);
	if (!philo->data->simulation_stop)
	{
		current_time = get_time() - philo->data->start_time;
		printf("%lld %d %s\n", current_time, philo->id, status);
		fflush(stdout);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	take_forks(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	if (philo->left_fork < philo->right_fork)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	pthread_mutex_lock(&philo->data->forks[first_fork]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[second_fork]);
	print_status(philo, "has taken a fork");
}

void	start_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->eating = 1;
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->data->death_mutex);
	print_status(philo, "is eating");
	ft_usleep(philo->data->time_to_eat);
}

void	finish_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->meals_eaten++;
	philo->eating = 0;
	pthread_mutex_unlock(&philo->data->death_mutex);
}

void	philo_eat(t_philo *philo)
{
	if (is_simulation_finished(philo->data))
		return ;
	if (philo->data->nb_philos == 1)
	{
		handle_single_philo(philo);
		return ;
	}
	take_forks(philo);
	start_eating(philo);
	finish_eating(philo);
	release_forks(philo);
}
