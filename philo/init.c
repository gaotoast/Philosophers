/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:05:01 by stakada           #+#    #+#             */
/*   Updated: 2025/07/30 17:34:54 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	parse_args(t_data *data, int argc, char **argv)
{
	data->n_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat_count = ft_atoi(argv[5]);
	else
		data->must_eat_count = -1;
	if (data->n_of_philos < 1 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0 || data->must_eat_count == 0)
	{
		write(2, "Error: Invalid argument values\n", 31);
		return (-1);
	}
	return (0);
}

static int	init_data(t_data *data, int argc, char **argv)
{
	int	i;

	if (parse_args(data, argc, argv) < 0)
		return (-1);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->n_of_philos);
	if (!data->forks)
		return (-1);
	i = 0;
	while (i < data->n_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) < 0)
			return (-1);
		i++;
	}
	return (0);
}

static int	init_philos(t_data *data)
{
	int	i;

	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->n_of_philos);
	if (!data->philos)
		return (-1);
	i = 0;
	while (i < data->n_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = NULL;
		data->philos[i].right_fork = NULL;
		data->philos[i].data = data;
		i++;
	}
	return (0);
}

int	init(t_data *data, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		write(2,
			"Usage: ./philo number_of_philosophers time_to_die time_to_eat "
			"time_to_sleep [number_of_times_each_philosopher_must_eat]\n",
			120);
		return (-1);
	}
	if (init_data(data, argc, argv) < 0 || init_philos(data) < 0)
		return (-1);
	return (0);
}
