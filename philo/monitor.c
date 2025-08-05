/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:13:07 by stakada           #+#    #+#             */
/*   Updated: 2025/08/05 22:56:30 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_death(t_philo *philo, t_data *data)
{
	long long	current_time;

	current_time = get_time_ms();
	if ((current_time - philo->last_meal_time) >= data->time_to_die)
	{
		if (!data->is_game_over)
			data->is_game_over = 1;
		print_state(philo->id, data, MSG_DIED);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&(philo->data->monitor_mutex));
		if (philo->data->is_game_over)
		{
			pthread_mutex_unlock(&(philo->data->monitor_mutex));
			break ;
		}
		if (check_philo_death(philo, philo->data) != 0)
		{
			pthread_mutex_unlock(&(philo->data->monitor_mutex));
			break ;
		}
		pthread_mutex_unlock(&(philo->data->monitor_mutex));
	}
	return (NULL);
}
