/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:37:42 by stakada           #+#    #+#             */
/*   Updated: 2025/08/04 12:56:40 by stakada          ###   ########.fr       */
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

int	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->monitor_mutex));
	if (philo->data->is_game_over)
	{
		pthread_mutex_unlock(&(philo->data->monitor_mutex));
		return (-1);
	}
	pthread_mutex_unlock(&(philo->data->monitor_mutex));
	print_state(philo->id, philo->data, MSG_SLEEP);
	ft_usleep(philo->data->time_to_sleep);
	return (0);
}

int	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->monitor_mutex));
	if (philo->data->is_game_over)
	{
		pthread_mutex_unlock(&(philo->data->monitor_mutex));
		return (-1);
	}
	pthread_mutex_unlock(&(philo->data->monitor_mutex));
	print_state(philo->id, philo->data, MSG_THINK);
	return (0);
}

// TODO: philo_eat
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&(philo->data->monitor_mutex));
	while (!philo->data->is_game_over)
	{
		pthread_mutex_unlock(&(philo->data->monitor_mutex));
		if (philo_sleep(philo) < 0)
			return (NULL);
		if (philo_think(philo) < 0)
			return (NULL);
		pthread_mutex_lock(&(philo->data->monitor_mutex));
	}
	pthread_mutex_unlock(&(philo->data->monitor_mutex));
	return (NULL);
}
