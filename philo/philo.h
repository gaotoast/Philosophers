/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 23:20:29 by stakada           #+#    #+#             */
/*   Updated: 2025/08/07 18:41:43 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define MSG_TAKE "has taken a fork"
# define MSG_EAT "is eating"
# define MSG_SLEEP "is sleeping"
# define MSG_THINK "is thinking"
# define MSG_DIED "died"

typedef struct s_data	t_data;

typedef enum s_turn
{
	TURN_ODD,
	TURN_EVEN,
	TURN_LAST,
}						t_turn;

typedef struct s_philo
{
	int64_t				id;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		meal_mutex;
	int64_t				last_meal_time;
	int64_t				meals_eaten;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	int64_t				n_of_philos;
	int64_t				time_to_die;
	int64_t				time_to_eat;
	int64_t				time_to_sleep;
	int64_t				must_eat_count;
	int64_t				start_time;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		monitor_mutex;
	int					end_flag;
	pthread_mutex_t		turn_mutex;
	t_turn				current_turn;
	int64_t				odd_done;
	int64_t				even_done;
	int64_t				last_done;
	t_philo				*philos;
	pthread_mutex_t		*forks;
}						t_data;

// init
int						init(t_data *data, int argc, char **argv);
int						check_args(int argc, char **argv);

// simulate
int						simulate(t_data *data);
void					print_state(int id, t_data *data, char *msg);

// philo
void					*philo_routine(void *arg);

// turn
int						is_my_turn(int philo_id, t_data *data);
void					report_turn_done(int philo_id, t_data *data);

// utils
int64_t					str_to_int64(const char *nptr);
int64_t					get_time_ms(void);
void					ft_usleep(int64_t ms, t_data *data);
int						handle_single_philo(t_philo *philo);

// clean_up
void					clean_up_data(t_data *data);

#endif