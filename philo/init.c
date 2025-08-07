/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:05:01 by stakada           #+#    #+#             */
/*   Updated: 2025/08/07 20:34:08 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	parse_args(t_data *data, int argc, char **argv)
{
	data->n_of_philos = str_to_int64(argv[1]);
	data->time_to_die = str_to_int64(argv[2]);
	data->time_to_eat = str_to_int64(argv[3]);
	data->time_to_sleep = str_to_int64(argv[4]);
	if (argc == 6)
	{
		data->must_eat_count = str_to_int64(argv[5]);
		if (data->must_eat_count <= 0)
		{
			write(STDERR_FILENO, "Error: Invalid argument values\n", 31);
			return (-1);
		}
	}
	else
		data->must_eat_count = -1;
	if (data->n_of_philos < 1 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
	{
		write(STDERR_FILENO, "Error: Invalid argument values\n", 31);
		return (-1);
	}
	return (0);
}

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
		|| pthread_mutex_init(&(data->monitor_mutex), NULL) != 0
		|| pthread_mutex_init(&(data->turn_mutex), NULL) != 0)
		return (-1);
	return (0);
}

static int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = &(data->forks[i]);
		data->philos[i].right_fork = &(data->forks[(i + 1)
				% data->n_of_philos]);
		data->philos[i].last_meal_time = 0;
		data->philos[i].meals_eaten = 0;
		data->philos[i].data = data;
		if (pthread_mutex_init(&(data->philos[i].meal_mutex), NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&(data->philos[i].meal_mutex));
			free(data->philos);
			data->philos = NULL;
			return (-1);
		}
		i++;
	}
	return (0);
}

static int	init_data(t_data *data, int argc, char **argv)
{
	if (parse_args(data, argc, argv) < 0)
		return (-1);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->n_of_philos);
	if (!data->forks)
		return (-1);
	if (init_mutexes(data) < 0)
		return (-1);
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->n_of_philos);
	if (!data->philos)
		return (-1);
	if (init_philos(data) < 0)
		return (-1);
	data->start_time = 0;
	data->end_flag = 0;
	data->current_turn = TURN_ODD;
	data->odd_done = 0;
	data->even_done = 0;
	data->last_done = 0;
	return (0);
}

int	init(t_data *data, int argc, char **argv)
{
	memset(data, 0, sizeof(t_data));
	if (init_data(data, argc, argv) < 0)
	{
		clean_up_data(data);
		return (-1);
	}
	return (0);
}
