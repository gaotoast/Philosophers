/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:37:42 by stakada           #+#    #+#             */
/*   Updated: 2025/08/07 17:52:58 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo->id, philo->data, MSG_TAKE);
		pthread_mutex_lock(philo->right_fork);
		print_state(philo->id, philo->data, MSG_TAKE);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_state(philo->id, philo->data, MSG_TAKE);
		pthread_mutex_lock(philo->left_fork);
		print_state(philo->id, philo->data, MSG_TAKE);
	}
}

int	philo_eat(t_philo *philo)
{
	while (!is_my_turn(philo->id, philo->data))
	{
		pthread_mutex_lock(&(philo->data->monitor_mutex));
		if (philo->data->end_flag)
		{
			pthread_mutex_unlock(&(philo->data->monitor_mutex));
			return (-1);
		}
		pthread_mutex_unlock(&(philo->data->monitor_mutex));
		usleep(100);
	}
	philo_take_forks(philo);
	pthread_mutex_lock(&(philo->meal_mutex));
	philo->last_meal_time = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&(philo->meal_mutex));
	pthread_mutex_lock(&(philo->data->monitor_mutex));
	print_state(philo->id, philo->data, MSG_EAT);
	pthread_mutex_unlock(&(philo->data->monitor_mutex));
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	report_turn_done(philo->id, philo->data);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->monitor_mutex));
	if (philo->data->end_flag)
	{
		pthread_mutex_unlock(&(philo->data->monitor_mutex));
		return (-1);
	}
	print_state(philo->id, philo->data, MSG_SLEEP);
	pthread_mutex_unlock(&(philo->data->monitor_mutex));
	ft_usleep(philo->data->time_to_sleep);
	return (0);
}

int	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->monitor_mutex));
	if (philo->data->end_flag)
	{
		pthread_mutex_unlock(&(philo->data->monitor_mutex));
		return (-1);
	}
	print_state(philo->id, philo->data, MSG_THINK);
	pthread_mutex_unlock(&(philo->data->monitor_mutex));
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (handle_single_philo(philo))
		return (NULL);
	while (1)
	{
		pthread_mutex_lock(&(philo->data->monitor_mutex));
		if (philo->data->end_flag)
		{
			pthread_mutex_unlock(&(philo->data->monitor_mutex));
			return (NULL);
		}
		pthread_mutex_unlock(&(philo->data->monitor_mutex));
		if (philo_eat(philo) < 0)
			break ;
		if (philo_sleep(philo) < 0)
			break ;
		if (philo_think(philo) < 0)
			break ;
	}
	return (NULL);
}
