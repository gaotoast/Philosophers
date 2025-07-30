/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:37:42 by stakada           #+#    #+#             */
/*   Updated: 2025/07/30 16:09:06 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo		*philo;
	long long	timestamp;

	philo = (t_philo *)arg;
	timestamp = philo->data->start_time - get_time_ms();
	printf("%lld %d %s\n", timestamp, philo->id, "Philosopher is alive");
	return (NULL);
}
