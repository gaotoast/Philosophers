/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:43:02 by stakada           #+#    #+#             */
/*   Updated: 2025/07/30 16:08:45 by stakada          ###   ########.fr       */
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
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine,
				(void *)&data->philos[i].id) != 0)
			return (-1);
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
