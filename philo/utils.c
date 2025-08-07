/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:05:24 by stakada           #+#    #+#             */
/*   Updated: 2025/08/07 19:00:19 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int64_t	str_to_int64(const char *nptr)
{
	int64_t	result;

	result = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (result > (INT64_MAX - (*nptr - '0')) / 10)
			return (-1);
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (result);
}

void	print_state(int philo_id, t_data *data, char *msg)
{
	int64_t	timestamp;

	if (data->end_flag)
		return ;
	pthread_mutex_lock(&(data->print_mutex));
	timestamp = get_time_ms() - data->start_time;
	printf("%lld %d %s\n", timestamp, philo_id, msg);
	pthread_mutex_unlock(&(data->print_mutex));
}

int64_t	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((int64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(int64_t ms, t_data *data)
{
	int64_t	start_time;
	int64_t	current_time;

	start_time = get_time_ms();
	current_time = start_time;
	while ((current_time - start_time) < ms)
	{
		pthread_mutex_lock(&(data->monitor_mutex));
		if (data->end_flag)
		{
			pthread_mutex_unlock(&(data->monitor_mutex));
			return ;
		}
		pthread_mutex_unlock(&(data->monitor_mutex));
		usleep(100);
		current_time = get_time_ms();
	}
}

int	handle_single_philo(t_philo *philo)
{
	if (philo->data->n_of_philos != 1)
		return (0);
	pthread_mutex_lock(philo->left_fork);
	print_state(philo->id, philo->data, MSG_TAKE);
	ft_usleep(philo->data->time_to_die, philo->data);
	pthread_mutex_unlock(philo->left_fork);
	return (1);
}
