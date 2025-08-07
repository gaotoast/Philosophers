/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:54:35 by stakada           #+#    #+#             */
/*   Updated: 2025/08/07 17:54:40 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		pthread_mutex_destroy(&(data->turn_mutex));
	}
	if (data->philos)
	{
		i = 0;
		while (i < data->n_of_philos)
		{
			pthread_mutex_destroy(&(data->philos[i].meal_mutex));
			i++;
		}
		free(data->philos);
	}
}
