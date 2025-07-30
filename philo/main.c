/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:13:45 by stakada           #+#    #+#             */
/*   Updated: 2025/07/30 22:18:59 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		ret;

	if (argc < 5 || argc > 6)
	{
		write(STDERR_FILENO, "Usage: ./philo number_of_philosophers ", 50);
		write(STDERR_FILENO, "time_to_die time_to_eat time_to_sleep ", 38);
		write(STDERR_FILENO, "[number_of_times_each_philosopher_must_eat]\n",
			44);
		return (-1);
	}
	if (init(&data, argc, argv) < 0)
		return (1);
	ret = simulate(&data);
	free_data(&data);
	if (ret < 0)
		return (1);
	return (0);
}
