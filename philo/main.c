/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:13:45 by stakada           #+#    #+#             */
/*   Updated: 2025/07/30 18:15:39 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (init(&data, argc, argv) < 0)
		return (1);
	if (simulate(&data) < 0)
	{
		free_data(&data);
		return (1);
	}
	return (0);
}
