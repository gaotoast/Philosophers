/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:43:02 by stakada           #+#    #+#             */
/*   Updated: 2025/08/06 17:51:47 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_death(t_data *data, int i)
{
	long long	current_time;
	long long	last_meal_time;

	current_time = get_time_ms();
	pthread_mutex_lock(&(data->philos[i].meal_mutex));
	last_meal_time = data->philos[i].last_meal_time;
	pthread_mutex_unlock(&(data->philos[i].meal_mutex));
	if ((current_time - last_meal_time) >= data->time_to_die)
	{
		pthread_mutex_lock(&(data->monitor_mutex));
		if (!data->end_flag)
		{
			print_state(data->philos[i].id, data, MSG_DIED);
			data->end_flag = 1;
			pthread_mutex_unlock(&(data->monitor_mutex));
			return (1);
		}
		pthread_mutex_unlock(&(data->monitor_mutex));
		return (1);
	}
	return (0);
}

int	check_all_ate_enough(t_data *data, int ate_flag)
{
	if (data->must_eat_count > 0 && ate_flag)
	{
		pthread_mutex_lock(&(data->monitor_mutex));
		data->end_flag = 1;
		pthread_mutex_unlock(&(data->monitor_mutex));
		return (1);
	}
	return (0);
}

int	monitor_simulation(t_data *data)
{
	int	i;
	int	all_ate_enough;

	while (1)
	{
		i = 0;
		all_ate_enough = 1;
		while (i < data->n_of_philos)
		{
			if (check_philo_death(data, i))
				return (1);
			if (data->must_eat_count > 0)
			{
				pthread_mutex_lock(&(data->philos[i].meal_mutex));
				if (data->philos[i].meals_eaten < data->must_eat_count)
					all_ate_enough = 0;
				pthread_mutex_unlock(&(data->philos[i].meal_mutex));
			}
			i++;
		}
		if (check_all_ate_enough(data, all_ate_enough))
			return (0);
		usleep(100);
	}
	return (0);
}

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_of_philos)
	{
		if (pthread_create(&(data->philos[i].thread), NULL, philo_routine,
				(void *)&(data->philos[i])) != 0)
		{
			while (--(i) >= 0)
				pthread_detach(data->philos[i].thread);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	simulate(t_data *data)
{
	int			i;
	int			ret;
	long long	current_time;

	current_time = get_time_ms();
	data->start_time = current_time;
	i = 0;
	while (i < data->n_of_philos)
	{
		data->philos[i].last_meal_time = current_time;
		i++;
	}
	if (create_threads(data) < 0)
		return (-1);
	ret = monitor_simulation(data);
	i = 0;
	while (i < data->n_of_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	return (ret);
}
