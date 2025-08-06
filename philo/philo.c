/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:37:42 by stakada           #+#    #+#             */
/*   Updated: 2025/08/06 14:09:17 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// TODO: take forks
int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->monitor_mutex));
	if (philo->data->is_game_over)
	{
		pthread_mutex_unlock(&(philo->data->monitor_mutex));
		return (-1);
	}
	pthread_mutex_unlock(&(philo->data->monitor_mutex));
	philo->last_meal_time = get_time_ms();
	print_state(philo->id, philo->data, MSG_EAT);
	ft_usleep(philo->data->time_to_eat);
	return (0);
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

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&(philo->data->monitor_mutex));
		if (philo->data->is_game_over)
		{
			pthread_mutex_unlock(&(philo->data->monitor_mutex));
			return (NULL);
		}
		pthread_mutex_unlock(&(philo->data->monitor_mutex));
		if (philo_eat(philo) < 0)
			break ;
		if (philo_sleep(philo) < 0)
			break ;
		if (philo_think(philo) < 0)
			break ;
	}
	return (NULL);
}
