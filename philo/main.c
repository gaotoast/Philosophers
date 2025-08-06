/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:13:45 by stakada           #+#    #+#             */
/*   Updated: 2025/08/06 17:39:37 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		ret;

	if (check_args(argc, argv) < 0)
		return (1);
	if (init(&data, argc, argv) < 0)
		return (1);
	ret = simulate(&data);
	clean_up_data(&data);
	if (ret != 0)
		return (1);
	return (0);
}
