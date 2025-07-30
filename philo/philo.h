/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 23:20:29 by stakada           #+#    #+#             */
/*   Updated: 2025/07/30 16:08:49 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	int					n_of_philos;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	int					must_eat_count;
	long long			start_time;
	t_philo				*philos;
	pthread_mutex_t		*forks;
}						t_data;

// init
int						init(t_data *data, int argc, char **argv);

// simulate
int						simulate(t_data *data);

// routine
void					*philo_routine(void *arg);

// utils
int						ft_atoi(const char *nptr);
long long				get_time_ms(void);

#endif