/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:05:01 by stakada           #+#    #+#             */
/*   Updated: 2025/08/05 19:41:23 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_of_philos)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&(data->forks[i]));
			free(data->forks);
			data->forks = NULL;
			return (-1);
		}
		i++;
	}
	if (pthread_mutex_init(&(data->print_mutex), NULL) != 0
		|| pthread_mutex_init(&(data->monitor_mutex), NULL) != 0)
		return (-1);
	return (0);
}

static int	init_data(t_data *data, int argc, char **argv)
{
	memset(data, 0, sizeof(t_data));
	if (parse_args(data, argc, argv) < 0)
		return (-1);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->n_of_philos);
	if (!data->forks)
		return (-1);
	if (init_mutexes(data) < 0)
		return (-1);
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
		data->philos[i].left_fork = &(data->forks[i]);
		data->philos[i].right_fork = &(data->forks[(i + 1)
				% data->n_of_philos]);
		data->philos[i].last_meal_time = LLONG_MAX;
		data->philos[i].data = data;
		i++;
	}
	return (0);
}

int	init(t_data *data, int argc, char **argv)
{
	if (init_data(data, argc, argv) < 0 || init_philos(data) < 0)
	{
		clean_up_data(data);
		return (-1);
	}
	return (0);
}
