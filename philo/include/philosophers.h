/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinzhang <jinzhang@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 19:56:29 by jinzhang          #+#    #+#             */
/*   Updated: 2025/12/30 17:52:11 by jinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	long				philo_id;
	long				meal_eaten;
	long				previous_meal;
	t_data				*data;
	pthread_t			thread_id;
	pthread_mutex_t		*left_forks;
	pthread_mutex_t		*right_forks;
	pthread_mutex_t		*meal_lock;

}						t_philo;

typedef struct s_data
{
	t_philo				*philo;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*print_lock;
	pthread_mutex_t		*end_simulation_lock;
	pthread_mutex_t		*meal_locks;
	long				end_simulation;
	long				start_simulation;
	long				philo_count;
	long				hunger_endurance;
	long				eat_duration;
	long				sleep_duration;
	long				meal_limit;

}						t_data;

// parsing.c
bool					input_validation(int argc, char **argv, t_data *d);

// init.c
bool					data_init(t_data *d);

// start_threads.c
bool					create_thread(t_data *d);
bool					join_threads(t_data *d);

// routine.c
bool					take_forks(t_philo *philo);
bool					are_eating(t_philo *philo);
void					put_down_forks(t_philo *philo);
void					precise_usleep(t_philo *philo, long sleep_duration);
bool					is_dead(t_philo *philo);

// monitor.c
void					main_monitor(t_data *d);
bool					simulation_over(t_data *d);

// utils.c
void					locked_printf(t_philo *philo, char *msg);
long					get_now_time_converter(void);

// cleanup.c
bool					cleanup_free(t_data *d, char *msg);
bool					cleanup_all(t_data *d, char *msg);

#endif
