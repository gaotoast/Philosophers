/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 20:08:24 by stakada           #+#    #+#             */
/*   Updated: 2025/08/05 18:49:56 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_valid_number(char *str)
{
	int	i;

	if (!*str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		write(STDERR_FILENO, "Usage: ./philo number_of_philosophers ", 38);
		write(STDERR_FILENO, "time_to_die time_to_eat time_to_sleep ", 38);
		write(STDERR_FILENO, "[number_of_times_each_philosopher_must_eat]\n",
			44);
		return (-1);
	}
	i = 1;
	while (i < argc)
	{
		if (!is_valid_number(argv[i]))
		{
			write(STDERR_FILENO, "Error: Invalid argument values\n", 31);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	parse_args(t_data *data, int argc, char **argv)
{
	data->n_of_philos = str_to_long(argv[1]);
	data->time_to_die = str_to_long(argv[2]);
	data->time_to_eat = str_to_long(argv[3]);
	data->time_to_sleep = str_to_long(argv[4]);
	if (argc == 6)
		data->must_eat_count = str_to_long(argv[5]);
	else
		data->must_eat_count = -1;
	if (data->n_of_philos < 1 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0 || data->must_eat_count == 0)
	{
		write(STDERR_FILENO, "Error: Invalid argument values\n", 31);
		return (-1);
	}
	return (0);
}
