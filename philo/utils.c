/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:05:24 by stakada           #+#    #+#             */
/*   Updated: 2025/08/04 18:49:30 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(int philo_id, t_data *data, char *msg)
{
	long long	timestamp;

	pthread_mutex_lock(&(data->print_mutex));
	if (!data->is_game_over)
	{
		timestamp = get_time_ms() - data->start_time;
		printf("%lld %d %s\n", timestamp, philo_id, msg);
	}
	pthread_mutex_unlock(&(data->print_mutex));
}

long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	free_data(t_data *data)
{
	free(data->forks);
	free(data->philos);
}

void	clean_up_data(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->n_of_philos)
		{
			pthread_mutex_destroy(&(data->forks[i]));
			i++;
		}
		free(data->forks);
		pthread_mutex_destroy(&(data->print_mutex));
		pthread_mutex_destroy(&(data->monitor_mutex));
	}
	if (data->philos)
		free(data->philos);
}
