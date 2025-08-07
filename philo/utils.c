/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:05:24 by stakada           #+#    #+#             */
/*   Updated: 2025/08/07 17:54:28 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	str_to_long(const char *nptr)
{
	long	result;

	result = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (result > (LONG_MAX - (*nptr - '0')) / 10)
			return (-1);
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (result);
}

void	print_state(int philo_id, t_data *data, char *msg)
{
	long long	timestamp;

	if (data->end_flag)
		return ;
	pthread_mutex_lock(&(data->print_mutex));
	timestamp = get_time_ms() - data->start_time;
	printf("%lld %d %s\n", timestamp, philo_id, msg);
	pthread_mutex_unlock(&(data->print_mutex));
}

long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long long ms)
{
	long long	start_time;
	long long	current_time;

	start_time = get_time_ms();
	current_time = start_time;
	while ((current_time - start_time) < ms)
	{
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
	pthread_mutex_unlock(philo->left_fork);
	return (1);
}
