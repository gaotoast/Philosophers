/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:43:25 by stakada           #+#    #+#             */
/*   Updated: 2025/08/06 15:45:15 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_my_turn(int philo_id, t_data *data)
{
	t_turn	turn;

	pthread_mutex_lock(&(data->turn_mutex));
	turn = data->current_turn;
	pthread_mutex_unlock(&(data->turn_mutex));
	if (philo_id % 2 != 0 && philo_id != data->n_of_philos && turn == TURN_ODD)
		return (1);
	if (philo_id % 2 == 0 && turn == TURN_EVEN)
		return (1);
	if (philo_id == data->n_of_philos && data->n_of_philos % 2 != 0
		&& turn == TURN_LAST)
		return (1);
	return (0);
}

static void	update_current_turn(t_data *data)
{
	int	odd_count;
	int	even_count;
	int	is_philos_odd;

	odd_count = data->n_of_philos / 2;
	even_count = data->n_of_philos / 2;
	is_philos_odd = data->n_of_philos % 2;
	if (data->current_turn == TURN_ODD && data->odd_done >= odd_count)
	{
		data->odd_done = 0;
		data->current_turn = TURN_EVEN;
	}
	else if (data->current_turn == TURN_EVEN && data->even_done >= even_count)
	{
		data->even_done = 0;
		if (is_philos_odd)
			data->current_turn = TURN_LAST;
		else
			data->current_turn = TURN_ODD;
	}
	else if (data->current_turn == TURN_LAST && data->last_done >= 1)
	{
		data->last_done = 0;
		data->current_turn = TURN_ODD;
	}
}

void	report_turn_done(int philo_id, t_data *data)
{
	pthread_mutex_lock(&(data->turn_mutex));
	if (philo_id % 2 != 0 && data->current_turn == TURN_ODD)
		data->odd_done++;
	else if (philo_id % 2 == 0 && data->current_turn == TURN_EVEN)
		data->even_done++;
	else if (philo_id == data->n_of_philos && data->current_turn == TURN_LAST)
		data->last_done++;
	update_current_turn(data);
	pthread_mutex_unlock(&(data->turn_mutex));
}
