/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:48:32 by stakada           #+#    #+#             */
/*   Updated: 2025/08/05 18:56:27 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	str_to_long(const char *nptr)
{
	long	result;

	result = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (result > (LONG_MAX - (*nptr - '0') / 10))
			return (-1);
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (result);
}

void	ft_usleep(long ms)
{
	usleep(ms * 1000);
}
