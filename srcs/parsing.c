/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourkai <rbourkai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:02:59 by rbourkai          #+#    #+#             */
/*   Updated: 2025/07/02 16:28:36 by rbourkai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *str, int *result)
{
	long	num;
	int		sign;
	int		i;

	num = 0;
	sign = 1;
	i = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		if (num * sign > INT_MAX || num * sign < INT_MIN)
			return (-1);
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (*result = (int)(num * sign), 0);
}

int	parse_args(int ac, char **av, t_data *data)
{
	if (ac > 6 || ac < 5)
		return (printf("Use 4 or 5 args\n"), -1);
	if ((ft_atoi(av[1], &data->nb_philos)) || (data->nb_philos <= 0))
		return (printf("Error: Invalid number of philosophers\n"), -1);
	if ((ft_atoi(av[2], &data->time_to_die)) || (data->time_to_die <= 0))
		return (printf("Error: Invalid time to die\n"), -1);
	if ((ft_atoi(av[3], &data->time_to_eat)) || (data->time_to_eat <= 0))
		return (printf("Error: Invalid time to eat\n"), -1);
	if ((ft_atoi(av[4], &data->time_to_sleep)) || (data->time_to_sleep <= 0))
		return (printf("Error: Invalid time to sleep\n"), -1);
	if (ac == 6)
	{
		if ((ft_atoi(av[5], &data->nb_must_eat)) || (data->nb_must_eat <= 0))
			return (printf("Error: Invalid number of meals\n"), -1);
	}
	else
		data->nb_must_eat = -1;
	return (0);
}

void	ft_usleep(int time_ms)
{
	long long	start_time;

	start_time = get_time();
	while (get_time() - start_time < time_ms)
		usleep(100);
}
