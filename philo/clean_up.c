/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:02:24 by stakada           #+#    #+#             */
/*   Updated: 2025/08/05 19:03:09 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_data(t_data *data)
{
	free(data->forks);
	free(data->philos);
}

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
	}
	if (data->philos)
		free(data->philos);
}
