/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:43:02 by stakada           #+#    #+#             */
/*   Updated: 2025/08/04 12:01:14 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	simulate(t_data *data)
{
	int	i;

	data->start_time = get_time_ms();
	i = 0;
	while (i < data->n_of_philos)
	{
		if (pthread_create(&(data->philos[i].thread), NULL, philo_routine,
				(void *)&(data->philos[i])) != 0)
		{
			while (--i >= 0)
				pthread_detach(data->philos[i].thread);
			return (-1);
		}
		i++;
	}
	i = 0;
	while (i < data->n_of_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	return (0);
}
