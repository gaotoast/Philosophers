/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:37:42 by stakada           #+#    #+#             */
/*   Updated: 2025/07/30 22:34:03 by stakada          ###   ########.fr       */
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

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	print_state(philo->id, philo->data, MSG_THINK);
	return (NULL);
}
