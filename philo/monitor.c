/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:13:07 by stakada           #+#    #+#             */
/*   Updated: 2025/08/05 19:33:20 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_death(t_philo *philo, t_data *data)
{
	long long	current_time;

	current_time = get_time_ms();
	if ((philo->last_meal_time - current_time) >= data->time_to_die)
	{
		if (!data->is_game_over)
			data->is_game_over = 1;
		pthread_mutex_lock(&(data->print_mutex));
		print_state(philo->id, data, MSG_DIED);
		pthread_mutex_unlock(&(data->print_mutex));
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	ft_usleep(1);
	while (1)
	{
		pthread_mutex_lock(&(philo->data->monitor_mutex));
		if (philo->data->is_game_over)
			break ;
		if (check_philo_death(philo, philo->data) != 0)
			break ;
		pthread_mutex_unlock(&(philo->data->monitor_mutex));
	}
	return (NULL);
}
