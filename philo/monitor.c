/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:13:07 by stakada           #+#    #+#             */
/*   Updated: 2025/08/06 14:21:29 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_death(t_philo *philo, t_data *data)
{
	long long	current_time;

	current_time = get_time_ms();
	if ((current_time - philo->last_meal_time) >= data->time_to_die)
	{
		print_state(philo->id, data, MSG_DIED);
		pthread_mutex_lock(&(data->monitor_mutex));
		if (!data->end_flag)
			data->end_flag = 1;
		pthread_mutex_unlock(&(data->monitor_mutex));
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
		if (philo->data->end_flag)
		{
			pthread_mutex_unlock(&(philo->data->monitor_mutex));
			break ;
		}
		pthread_mutex_unlock(&(philo->data->monitor_mutex));
		if (check_philo_death(philo, philo->data) != 0)
			break ;
	}
	return (NULL);
}
